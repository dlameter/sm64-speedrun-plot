import srcomapi, srcomapi.datatypes as dt
import json
import time
api = srcomapi.SpeedrunCom(); api.debug = 1

# Find super mario 64
game = api.search(srcomapi.datatypes.Game, {"name": "super mario 64"})[0]

# Get dict with all runs
sm64_runs = {}
for category in game.categories:
  if not category.name in sm64_runs:
    sm64_runs[category.name] = {}
  if category.type == 'per-level':
    for level in game.levels:
      sm64_runs[category.name][level.name] = dt.Leaderboard(api, data=api.get("leaderboards/{}/level/{}/{}?embed=variables".format(game.id, level.id, category.id)))
  else:
    sm64_runs[category.name] = dt.Leaderboard(api, data=api.get("leaderboards/{}/category/{}?embed=variables".format(game.id, category.id)))

# Retrieve username
def get_username(player):
    if isinstance(player, srcomapi.datatypes.Guest):
        return player.name
    else:
        return player.names["international"]


# Build list of runs
def build_run_list(runs):
    output = []

    for run in runs:
        run_dict = {}

        retry = True
        while retry:
            try:
                run_dict = {}

                run_dict["place"] = run["place"]
                run_dict["time"] = run["run"].times["primary_t"]
                run_dict["submitted_date"] = run["run"].date
                run_dict["username"] = get_username(run["run"].players[0])

                retry = False
            except ValueError:
                retry = True
                print("Rate limit reached. Waiting 60 seconds before retrying...")
                time.sleep(60)
                print("Execution restarted")

        output.append(run_dict)

    return output

# build dict with wanted data
out = {}
for category in sm64_runs:
    if not category in out:
        out[category] = {}
    if isinstance(sm64_runs[category], dict):
        # build level dicts
        for level in sm64_runs[category]:
            #build runs
            out[category][level] = build_run_list(sm64_runs[category][level].runs)
    else:
        # build runs
        out[category]["runs"] = build_run_list(sm64_runs[category].runs)

# Write output to file
output_file = open("output.json", "w")
output_file.write(json.dumps(out))

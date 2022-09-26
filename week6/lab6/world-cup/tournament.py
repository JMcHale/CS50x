# Simulate a sports tournament

import csv
import sys
import random
import math

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # TODO: Read teams into memory from file
    #creates an empty list called teams
    teams = []
    bigteamdict = {}

    #stores the first arguement entered in the command line as "filename"
    filename = sys.argv[1]

    with open(filename, "r") as file:
        reader = csv.DictReader(file)

        #For each newline in the CSV file, do this
        for row in reader:
            """
            #set team to the value of the "team" key, found by column
            team = row["team"]
            #set rating to the value of the "rating" key, found by column, and convert this to an int
            rating = int(row["rating"])
            #create a dictionary with team as the key and rating as the value
            teamdict =  {
                team: rating
            }
            #append this dictionary to the end of the teams list
            teams.append(teamdict)
            bigteamdict[team]=rating
            """
            row["rating"] = int(row["rating"])
            teams.append(row)


        print(teams)
        #print(bigteamdict)

    counts = {}

    # TODO: Simulate N tournaments and keep track of win counts

    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] += 1
        else:
            counts[winner] = 1
    print (counts)

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    roundnumber = int(math.sqrt(len(teams)))
    print (roundnumber)
    remainingteams = teams
    for rounds in range(roundnumber):
        remainingteams = simulate_round(remainingteams)

    return remainingteams[0]["team"]

if __name__ == "__main__":
    main()

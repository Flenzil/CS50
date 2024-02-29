# FIFA Team Optimiser
#### Github: https://github.com/Flenzil/FifaOptimalPosition
#### Video Demo: https://youtu.be/WszhO3Q05pU
#### Description:
The online FIFA player database FUTbin has the information of tens of thousands players: names, ratings, special cards etc.
This project takes an input of 10 players (no need to enter the goalkeeper) and finds the best formation to play those players in and which
positions they should play in, in order to maximise the "Rating per Position" stat available on FUTbin.

The project is split into several modules, organised into a package which is called by main.py.

Outside of that structure, there is also updater.py which ensures that the list of players in player_info.csv is up to date with FUTbin's
database. Initially, player_info.csv was created from an hours-long scraping of FUTbin's information so now the programme runs very quickly,
even though it's all written in Python! (~20ms on average.)

And that's about it. It's a simple concept, even though it was quite complex to impliment and ended up with far more line of code than I initially
thought it would take. I'm also planning on trying to expand this into a chrome extension so that the user doesn't need to manually input player
details, instead the extension would grab the information from the webpage directly. This python script would need to be hosted somewhere, probably
as a lambda function through AWS. As of right now though, that part of the project has barely been touched.

```
        ,----,
   ___.`      `,
   `===  D     :
     `'.      .'
        )    (                   ,
       /      \_________________/|
      /                          |
     |                           ;
     |               _____       /
     |      \       ______7    ,'
     |       \    ______7     /
      \       `-,____7      ,'
^~^~^~^`\                  /~^~^~^~^
  ~^~^~^ `----------------' ~^~^~^
 ~^~^~^~^~^^~^~^~^~^~^~^~^~^~^~^~
 CS50 Duck
```
## Contents
### main.py
Simply calls the other modules and prints the result.
### classes.py
Defines the player and team objects. The team object contains a dictionary of player objects which will be filled in the optimiser. This
project was initially entirely functional but I think adding some object-orientated aspects improved the code overall.
### grab.py
Loads players in from players.csv and creates an array of player objects using the information from player_info.csv
### optimise.py
Finds the optimal formation for the given set of players and what positions to play them in. Limits the search to only formations that
can support the given players (e.g if 3 CB players are inputted, 4 at-the-back formations are invalid.)
### updater.py
Adds any newly released players to player_info.csv. Also updates "live" players: those whose stats can change over time or through certain
events.


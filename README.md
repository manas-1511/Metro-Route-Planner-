# Metro Route Planner

A C++ CLI app to find shortest and cheapest routes on the Delhi Metro. 
Built this for my semester 3 DSA project.

## What it does
- Find shortest path between any two stations (Dijkstra)
- Find cheapest route (cost-weighted Dijkstra)  
- Find fewest stops (BFS)
- Metro card with recharge and fare deduction
- Generates visual route maps using Graphviz

## How to run

Install graphviz first:
sudo apt-get install graphviz libgraphviz-dev

Then:
make
./metro

## File structure
- metro.cpp — main menu and auth
- graph_operations.cpp — all graph/routing logic
- card_operations.cpp — card balance and fare deduction

## Notes
Credentials are stored in usernames.txt (sorted, binary search for login).
Route maps are saved as PNGs in the project folder.

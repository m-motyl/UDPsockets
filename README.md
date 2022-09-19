# Rock paper scissors game based on datagram sockets (UDP)
A client-server application based on communication over datagram sockets in the Internet domain.
The application implements the game of rock paper scissors. The game is played in rounds and each player
makes a choice (paper, rock or scissors) and sends it to the server via his client. The server determines the result of
who won and sends the client of each player appropriate information (win, lose or draw).
There are two players (using the same program) and a server. The player sends his choice and waits for the server response 
until other player also sends his choice to the server. Each player counts his points and displays them in his window 
after each round (server program also displays the points of both players). After recieving "end" message from any clients, 
server clears the score and goes back to its initial state, waiting for a new pair of players

The server and players clients operate locally (IP 127.0.0.1). They exchange numeric messages which are game state numbers or 
players choices numbers. The server port is known to players and the players port numbers are automatically created when their clients
are created and remembered by the server to distinguish between players (the players can make their choices in a different order,
but their port numbers are the same in next rounds).

## remarks
* run server program first
* run programs (server and two players) in separate terminals

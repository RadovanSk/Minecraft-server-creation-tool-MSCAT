# Minecraft-server-creation-tool-MSCAT
MSCAT is a tool that creates .bat file for your .jar minecraft server file according to JVM arguments you have picked. I made this tool as a homework for school and ended up polishing it a little bit after the success with the homework. The intention of this tool is to make it easier for people who do not know about JVM arguments to make a server for themselves and their friends. All JVM arguments are briefly explained when hovering your mouse over "(?)" symbols. All default values are already set in the code itself so it's impossible to ruin the .bat file without doing anything except -XX:ParallelGCThreads which can't have default value due to varying hardware. You'll have to put in your own value in the app once G1 Garbage Collector is turned on. If by any chance your anti-virus detects this tool as a "virus" then do not worry. It's a simple tool which creates a file at best.

## How to use it
1. Download the MSCAT folder, extract it and run the .exe file. 
2. Type in/check your desired values for JVM arguments.
3. Click the "Create .bat file" button.

## Editing
If you want to edit the code privately then the only thing you need to do is to copy all the files from the source folder. You'll also need Dear ImGui for it to work.

## Note
I hope you'll like this simple tool. When it comes to programming, I am not perfect, nor close to being remotely "good" I believe, but I might be wrong. If you have any ideas or suggestions feel free to make a comment or edit the code. If there are any errors or my code being "spaghetti code" I'll take any criticism and suggestions. Or if there's anything else wrong feel free to tell me. Programming is what I plan to do for a living so I have to start somewhere and accept that I'm not as good as I want to be, yet. Once I feel like I have enough knowledge about programming and ideas for the tool I'll start making version 2.0.

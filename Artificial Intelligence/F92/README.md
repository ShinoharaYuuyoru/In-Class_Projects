# F92

#### Intro

This is an AI developed for classic RTS game StarCraft using [BWAPI](https://github.com/bwapi/bwapi)
The name of this repo was inspired by the name of a famous Chinese Starcraft Player——[F91](http://wiki.teamliquid.net/starcraft2/F91)

Special thanks to [David Churchill](https://github.com/davechurchill) for creating the example of [UAlbertabot](https://github.com/davechurchill/ualbertabot)

#### Setup

1. Install BWAPI on your computer. Go to [this page](https://github.com/bwapi/bwapi/releases) to download BWAPI
2. Install [BWTA2](https://bitbucket.org/auriarte/bwta2/downloads) on your computer
3. You need [Visual Studio 2013](https://msdn.microsoft.com/en-us/library/dd831853(v=vs.120).aspx) to build this bot
4. You also need a copy of Starcraft:BroodWar v1.16.1 in order to run this bot

#### Build

1. Set Environment Variables
   - `BWAPI_DIR` - BWAPI 4.1.2 installation root directory
   - `BWTA_DIR` - BWTA 2.2 installation root directory
2. Open F92.sln File in Visual Studio 2013
3. Change the Config file Path in `Config.cpp`
4. Select `Release` Mode
5. Build & Get `F92.dll` in Release Folder
6. Open `Chaos Launcher` modify the `config.txt` to use the dll file you've just built
7. Run Starcraft & Enjoy! 


# Nilts

```
┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━┓
┃ Current Development Status:  ┃ HEAVY ┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━━┫
┃ Current Development Version: ┃ 0.0.0 ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━┛
```

![alt tag](https://raw.githubusercontent.com/zesterer/nilts/master/misc/screen.png "A screenshot of development taken fairly recently")

### What is Nilts?

Nilts is a 3D game set within a mythical world. Designed from the start with multi-player in mind, Nilts is a game designed to be as involving and complex as is possible for a game.

Most of the content within the game is procedurally generated at runtime - anything from the plot, plants, terrain, NPC AI, names, species, political groups, weapons, foodstuffs, biomes, caves, dungeons, buildings, hamlets, villages, towns, cities, paths, trade links, boats, airships and other vehicles to animals, vegitation, forests, rivers, waterfalls, oceans, lakes, fjords, the sky, literature, languages, speech, customs, rituals, religions, cultural groups, clothing, armour and abilities. In Nilts, you get a different experience every time you play.

### Why make Nilts procedurally generated?

Nilts is designed to be this way for several reasons:

- Procedurally generated content is far more varied than anything a human could ever concieve.
- Generating content on the fly means a more lightweight game with more space for visual effects and procedural content.
- Procedural content means I spend less time building assets and more time actually writing software that builds the content.
- I'm a terrible artist and can't afford a good one.

### What dependencies does Nilts have?

Nilts depends on several libraries and programs. They are:

##### Non-essential

- git *[For cloning this repository]*
- cmake *[For compiling Nilts]*

##### Essential

- glfw3 *[For creating the window and GL contexts]*
- glbinding *[For the OpenGL API Nilts uses]*
- glm *[For mathematical operations]*
- libc *[C and C++ standard library]*

### What platforms does Nilts run on?

I develop Nilts currently on a computer running Arch Linux. As a result, if you want stability, it's probably best to run it on a Linux system.

That said, Nilts makes use of cmake, a cross-platform build system, and I have been careful to only use libraries that are cross-platform, so it's completely feasible to imagine that Nilts may compile and run on other systems such as Microsoft's Windows, BSD and Apple's OSX with only a little bit of tweaking.

### How can I get a copy of, compile, and run Nilts?

*Assuming you're running a Linux system with 'git' pre-installed*

##### Downloading

Navigate to a suitable directory, and run the following command:

`git clone https://github.com/zesterer/nilts`

This will clone a copy of the Nilts repository into the current directory.

Navigate to the Nilts root directory as follows.

`cd nilts`

Remove the existing libvolume link as follows.

`rm libvolume`

Clone another version into its place as follows.

`git clone https://github.com/zesterer/libvolume`

##### Compiling

*Assuming you've just downloaded Nilts via the methods shown above*

*Assuming you're running a Linux system with 'cmake' pre-installed, along with other dependencies mentioned above*

Create a build directory as follows.

`mkdir build/`

Navigate to the build directory as follows.

`cd build`

Use cmake to ready the source for compilation as follows.

`cmake ..`

Compile Nilts as follows.

`make`

##### Running

*Assuming you have downloaded and compiled Nilts as explained above*

Run the Nilts executable as follows.

`./nilts`

### Why 'Nilts'?

Nilts is an acroynm for 'New and Improved Leon Trotsky Simulator'. Don't ask me why. I think it originated as a joke between friends.

### How is Nilts licensed?

Nilts and all code within the "src" directory of this repository is licensed under GPL 2 unless explicitly explained otherwise. Any libraries included with this repositories are licensed seperately as their creator intended.

### I've found a bug. What do I do?

Oh dear. Sorry about that. Nilts is a very complex game, and there's not much I can do about the odd bug popping up here and there. Please report it in the issues page so I can have a go at fixing it.

### Why didn't you use an existing game engine?

I know there exist game engines like Unity that make game development significantly faster, but I choose not to use them for several reasons.

1. Unity is overkill. It has a lot of features, and a lot of redundancy. I know that games don't need to package this all together, but there still exists redundancy in it's runtime.

2. Unity isn't designed for a game like Nilts. Nilts is vastly different to most games in the way it renders and deals with data.

3. Writing a game from the ground-up in raw C++ and OpenGL is fun. It seriously is. I write software because I enjoy the challenge, not because I'm interested in making the final product. The journey is the most enjoyable part for me.

4. Unity is designed to deal with static game resources like textures and 3D models. It's designed to deal with low-poly moving entities and high-poly static world geometry. That's not how Nilts works. Nilts is extremely dynamic in it's use of data.

### I have an idea for a feature!

That's great. Post it in the issues section (please label it as an enhancement) and I'll take a look at it. Bear in mind that since Nilts is procedurally generated, many features are already built into the game and emerge through the random procedural generation that takes place as the game is played.

### I want to donate and support development

No you don't. There are people dying all over the world because they can't get access to clean drinking water and fulfill their basic human needs. There are people working under conditions that amount to little more than slavery simply to keep their families alive. If you want to help make me happy, donate some money to a reputable charity who will actually change things. I don't need money, but there are many people in this world who do.

### Credits

There are many people who have aided me in development on Nilts, and no doubt this list will grow as I develop further. Here are just a few:

- A certain Quint Thrithe
- The many people I've asked questions to on IRC (FreeNode: ##c++, ##opengl, ##c, etc.)

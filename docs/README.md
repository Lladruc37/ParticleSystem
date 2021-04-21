This project was created by [Sergi Colomer Ferrer](https://github.com/Lladruc37) for the Project II subject in the Bachelor's degree in Video Game Design and Development, under the supervision of [Ramon Santamaria Pena](https://github.com/raysan5)


# Index
- [Introduction](#introduction)
- [Market study](#market-study)
- [My approach](#my-approach)
- [TODO's and Solutions](#todos-and-solutions)
- [Possible improvements](#possible-improvements)
- [Documentation](#documentation)


# Introduction
A particle system is a structure that allows you to simulate particles of different types in a somewhat organic way with the advantage of just tweaking some particle properties to get the exact results you want very quickly and without much effort. Particle systems are highly object oriented. Particle systems are quite important in games in order to add to the visual representation of the whole feel of the game, you could say they are what gives life to the game.

Organic effects are difficult to simulate but what particle systems do is simplify the problem. By managing a large group of particles we can represent natural effects like water, fire or smoke so much easier than if we tried to treat it as a whole thing. Nowadays particle systems can be found in  almost any (dare I say every) game engine or 3D software.

I want to keep my program understandable for everyone and generic enough that anyone could implement in their project with almost no modifications. I also want to have a well structured and flexible system. If you have a good structure, you should be able to easily create new particle effects on top of it with little resistance. Of course the base code should be solid and work properly. This system should be flexible enough to develop new and more complex features adding to the particle system.

Another important thing that I want to remark is that the way I’m going to explain how to implement the system is definitely not unique and probably not the best. There are lots of ways to do this and there is plenty of professional people that know a lot more that I do. If you want to learn more about how to implement a particle system I encourage you to check the [documentation](#documentation) that helped me doing this.

By the end of the web, if you have been following with the exercises you should get something like this:



A particle system is a structure that allows you to simulate particles of different types in an organic way with the advantage of just tweaking some particle properties to get the exact results you want very quickly and without effort. And the best part: you don’t have to draw any of these particles. You just need a base texture and that’s all. The system will be in charge of rendering the particles, the effects (such as glowing), physics calculations, emission rate and so on. You don’t need to worry about anything, just playing around with it to get what you want.

Particle systems are quite important in games in order to add to the visual representation of the whole feel of the game. Particle systems are quite easy to write and are merely a collection of one or more particles. So we need to create a single particle with some properties and then let the particle system decide how many particles it wants.

Particle systems are highly object oriented. First make a class that represents the individual particles, and have these incorporate a lifespan variable that will tell the particle how long it has to live. This way, it will die out after a certain period of time. Next, make a class that acts as an "emitter", who's job is to maintain a collection of the particle class that you've already made. The emitter will initialize new particles, which are generally given an initial velocity and then are affected by forces on the system like gravity or wind. When a particle dies out, a new particle can be emitted from the source in its place.

A particle system contains a bunch of tiny objects called particles that have some kind of movement and a lifetime. These particles are generated and destroyed over time to simulate a flow. Hence, a particle system is the structure in charge of managing the living particles and generate new ones when needed.
Organic effects are difficult to simulate but what particle systems do is simplify the problem. Like in physics, we divide the effect in tiny and controllable particles that as a whole seems like something bigger that behaves as natural phenomenas. By managing a large group of these particles we can represent natural effects like water, fire or smoke so much easier than if we tried to treat it as a whole thing.
Nowadays particle systems can be found in any almost any game engine or 3D software. Maya and 3D Max have one as well as Unity or Unreal Engine. Particle are really important in a lot of videogames as it makes huge improvement. Particles makes the enviroment or the the player stands out and it really adds up a lot to the game. Let’s see a few examples.




END RESULT GIF----------------------

Let's see what's out there in the internet.

# Market study
It's quite common to work with sprites and sprite sheets, which for those unfamiliar with the term it's just a texture used to render both static and animated elements in a game. Ususally, nowadays less, these images are in pixel art form.

Here you have some examples of different sprite sheets:

MEGA MAN IMAGE---------------------

SAMUS IMAGE------------------------

EXPLOSION IMAGE--------------------

Even though this particle system is made considering a 2D game, here you have a 3D example:

3D EXPLOSION GIF-------------------

Let's see what composes a particle system.

## Components
### Particle system

The particle system in itself contains all emitters created, defines the emitter behaviour and properties and both spawns and despawns emitters if told to do so. It's in charge of managing everything particle related for us so we don't have to touch any of the emitter and particle code to affect these.

William T. Reeves, Researcher at Lucasfilm who worked in one of the first implementations of a particle system, describes one as such:
> “A particle system is a collection of many minute particles that together represent a fuzzy object. Over a period of time, particles are generated into a system, move and change from within the system, and die from the system.”

A particle system can be composed of various different kind of emitters that at the same time can also have emitters inside of them. This parent-child relation can go on as far as we want, depending of what we want to simulate it would be very useful. By using this hierearchy there’s a particle system which acts as a parent and contains subsystems that contains other subsystems.

### Emitter

An emitter is the object in charge of spawning all the particles and defining the particles behaviour and properties, very similar to the particle system to the emitter. An emitter is in charge of the following parameters:

- The emission rate of particles. As it's him the one creating them each frame it basically means how many particles are spawned per frame.
- The postion where the particles are generated. That could mean the same position of the emitter or a different one (usually) in relation to the emitter's position.
- The particle's velocity and movement in the scene.
- The particle's life until it is destroyed.
- Other particle properties like color, transparency, size...

The emitter itself contains all the particles that will be updated, drawn and eventually die over a period of time. All this data is transfered from the emitter to all this particles so they behave like they are suposed to. Changing this data will change the particles of that emitter too, affecting their behaviour accordingly.

### Particle

As said before particles inherit its properties from the emitter they came from. But what is exctly the particle itself? The particle itself it’s just a simple moving texture that is renderered on screen. In 3D enviroments they use something called billboards which is basically an image that always faces the camera. But we don’t need to worry about that as we will focus only in 2D.

This texture can be anything we want that fits our purpose. It’s almost always a balck and white texture that will be colored when rendering. A good example is this set of particle textures I gathered:

PARTICLE ATLAS-----------------

Particle properties along with the emitter can be anything you like. As an example, the Unity engine has a big spectrum when it comes to emitters and particle properties, which of course you can change anything you want thus allowing you to generate almost any type of particle you can think of.

David Finseth, Technical Artist at Synapse Games describes particle effects like so:
> *"Particle effects are a unique tool that can add interactivity and responsiveness to your games. They excel at creating a lot of movement and impact. Particle effects can be used to create magical fireballs, swirling dimensional portals, or for directing the player's attention to a glowing treasure chest."*

Here you have a video I found very interesting of how particles are done in League of Legends and a bit of explanation from one of the devs:

<iframe width="560" height="315" src="https://www.youtube.com/embed/{OczfR1UhMPg}" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


How are this particles managed thorugh the system? Do we need to generate a new particle every time? If so, will this affect the overall preformance of the game? Let's see what I have done when implementing this theory.

# My approach
How I did the particle system

# TODO's and Solutions
All TODO's with it's solutions and a bit of explanation

# Possible improvements
what could be improved

# Documentation
Links used

- [https://www.khanacademy.org/computing/pixar/effects/particle/v/effects-overview](https://www.khanacademy.org/computing/pixar/effects/particle/v/effects-overview) --
- [https://www.youtube.com/watch?v=6Z5FI5180oo](https://www.youtube.com/watch?v=6Z5FI5180oo)
- [https://github.com/scarsty/SDL2-particles](https://github.com/scarsty/SDL2-particles)
- [https://www.youtube.com/watch?v=eyo9jRsJBwY](https://www.youtube.com/watch?v=eyo9jRsJBwY) --
- [https://discourse.libsdl.org/t/2d-lighting-particle-effects/20480](https://discourse.libsdl.org/t/2d-lighting-particle-effects/20480)
- [https://www.pascalgamedevelopment.com/showthread.php?5863-SDL-amp-2d-particles](https://www.pascalgamedevelopment.com/showthread.php?5863-SDL-amp-2d-particles)
- [https://www.reddit.com/r/learnprogramming/comments/8up5q9/c_sdl2_particle_system_tutorials/](https://www.reddit.com/r/learnprogramming/comments/8up5q9/c_sdl2_particle_system_tutorials/)
- [https://gamedev.stackexchange.com/questions/33670/what-features-do-basic-particle-engines-have](https://gamedev.stackexchange.com/questions/33670/what-features-do-basic-particle-engines-have)
- [http://buildnewgames.com/particle-systems/](http://buildnewgames.com/particle-systems/) --
- [https://www.bfilipek.com/2014/04/flexible-particle-system-start.html](https://www.bfilipek.com/2014/04/flexible-particle-system-start.html) -
- [https://subscription.packtpub.com/book/game_development/9781785882722/9/ch09lvl1sec85/creating-a-particle-system](https://subscription.packtpub.com/book/game_development/9781785882722/9/ch09lvl1sec85/creating-a-particle-system)
- [https://www.youtube.com/watch?v=OczfR1UhMPg](https://www.youtube.com/watch?v=OczfR1UhMPg) --
- [https://stackoverflow.com/questions/11910181/how-to-implement-direction-in-a-2d-particle-system](https://stackoverflow.com/questions/11910181/how-to-implement-direction-in-a-2d-particle-system) -
- [https://gamedev.net/forums/topic/380009-where-can-i-find-a-2d-particle-system-tutorial/380009/](https://gamedev.net/forums/topic/380009-where-can-i-find-a-2d-particle-system-tutorial/380009/) --
- [http://wiki.libsdl.org/CategoryRender?highlight=%28particle%29](http://wiki.libsdl.org/CategoryRender?highlight=%28particle%29)
- [https://gamedev.net/forums/topic/627017-2d-particle-effects-39where-do-i-begin39/4954379/](https://gamedev.net/forums/topic/627017-2d-particle-effects-39where-do-i-begin39/4954379/) --
- [https://www.youtube.com/watch?v=f2zZfj8eq_Q&feature=emb_title](https://www.youtube.com/watch?v=f2zZfj8eq_Q&feature=emb_title)
- [http://gameprogrammingpatterns.com/object-pool.html](http://gameprogrammingpatterns.com/object-pool.html) --
- [http://gameprogrammingpatterns.com](http://gameprogrammingpatterns.com)
- [https://gamedevelopment.tutsplus.com/tutorials/adding-turbulence-to-a-particle-system--gamedev-13332](https://gamedevelopment.tutsplus.com/tutorials/adding-turbulence-to-a-particle-system--gamedev-13332) --
- [https://github.com/nintervik/2D-Particle-System](https://github.com/nintervik/2D-Particle-System) --
- [https://github.com/nintervik/2D-Particle-System/tree/master/docs](https://github.com/nintervik/2D-Particle-System/tree/master/docs) --
- [https://nintervik.github.io/2D-Particle-System/](https://nintervik.github.io/2D-Particle-System/) --
- [https://www.gamasutra.com/blogs/DavidFinseth/20180216/314707/Creating_2D_Particle_Effects_in_Unity3D.php](https://www.gamasutra.com/blogs/DavidFinseth/20180216/314707/Creating_2D_Particle_Effects_in_Unity3D.php) --

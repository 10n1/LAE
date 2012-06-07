# Laeko Engine #

The Laeko Engine is primarily for being awesome.

## Features ##

* Cross platform support
* Full Lua scripting
* Modern component-based entity system

## Usage ##

Laeko is designed to be used however you want it. It tries to impose as little as possible on the user. Because of this it offers a very C-like API of functions that act on data.

Every subsystem of the Laeko engine (graphics, scripting, etc) can be used independently. This allows the user to use the engine in almost anyway he or she deems fit, however it does place some more work on the users shoulders.

The main loop of the game is actually handed by the user, not the engine. This will requre the user to write platform-dependent main loops, but also allows flexibility to support new platforms without the engine needing an update. The engine comes with blank implementations of most systems (Windows, OS X, iOS, Android) main loop to get you started.

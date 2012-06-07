# Laeko Engine #

The Laeko Engine is primarily for being awesome. It's also __very__ much a work in progress. 

## Features ##

* Cross platform support
* Full Lua scripting
* Modern component-based entity system

## Usage ##

Laeko is designed to be used however you want it. It tries to impose as little as possible on the user. Because of this it offers a very C-like API of functions that act on data.

Every subsystem of the Laeko engine (graphics, scripting, etc) can be used independently (when applicable). This allows the user to use the engine in almost anyway he or she deems fit, however it does place some more work on the users shoulders.

The main loop of the game is actually handed by the user, not the engine. This will requre the user to write platform-dependent main loops, but also allows flexibility to support new platforms without the engine needing an update. The engine comes with blank implementations of most systems (Windows, OS X, iOS, Android) main loop to get you started.

Heres a very simple pseudocode example:

    main()
    {
		system_specific_window myWindow = make_OS_window();

    	lae_graphics graphics = lae_graphics_create(myWindow);
    	lae_scripting scripting = lae_scripting_create();
    	lae_audio audio = lae_audio_create();
    	
    	lae_core core = lae_core_create(graphics, scripting, audio);
    
    	while(running)
    	{
    		if(os_message)
    		{
    			do_specific_os_handling();
    			otherwise_pass_event_such_as_input_to_the_core(message);
    		}
    		lae_core_frame();
    	}
    }

Once the core is created with each subsystem, it's the only system you need to interact with. The core will then control each of them and call their appropriate functions (Present, MoveListener, etc) when it has to. You can keep the references to each specific subsystem to manually control them and you can also change/modify the subsystems that the core is using. This means you could tell the core that it no longer has a graphics device and it will just stop rendering and continue.

Any message that you don't need to handle can just be passed off to the engine core for it to handle. This would include things like resizes and input messages. This adds a bit of work to the user and can (and maybe should) be streamlined later.

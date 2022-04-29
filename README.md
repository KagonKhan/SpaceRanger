# SpaceRanger
A 2D space shooting game, utilizing the SFML library. The game style choice was inspired by the *Space Invaders* title. Many game techniques (natural movement, tracking systems, collision detection) and design patterns (singletons, commands, inheritance trees, flyweights, states, factories) have been utilized. Additionally, a GUI system has been implemented.


## Features
 - 3 weapon types (laser, beam, missile)
 - Many types of enemies (weapon tracking, homing missile, spline-based path)
 - RNG based backgrounds
 - GUI system
 - Slow motion part
 - Animations

## About
### Animations
Spritesheet base animation type has been provided. Animations are utilized for the `Beam` and `Missile` weapon types, for the exhaust of Player - changing intensity based on flight direction, and for `onDeath` events, such as explosions of missiles

### GUI system
Provided GUI enables keybinds via the `action` family. Implemented GUI layouts consist of `HorizontalLayout`, `VerticalLayout`, `TableLayout`, and `UnorderedLayout`.
Implemented widgets consist of `Label`, `TextButton`, `SpriteButton`, `CheckboxButton`, and `ArrowSwitchButton`

<table>
    <tr>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/MenuState.png?raw=true" alt="example" title="Example 1" width="350" />
        </td>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/OptionsState.png?raw=true" alt="example" title="Mayhem version" width="350" />
        </td>
    </tr>
</table>


### Enemies
Implemented ship types: Beam, Boss, Minigun, Missile, Scouts, Stealth, Tank. All of them having various stats (HP, speed, armor) with Missile, Minigun, Stealth being more distinct. The first one shoots homing missiles at the player, the second tracks player's movement aiming directly at them, the last one has a different type of pathing, based on splines.

### Movement
Player's movement is realized using WSAD keys. Enemy movement is realized in 2 ways; A movement queue based on direction and length, and Spline path for more natural movement with gradual change of direction.

### Background during gameplay
It pans the stars in the background, spawns nebulae and planets, and moves
them downwards creating the illusion of movement. The background is generated
randomly. The nebulae have three basic images, which are then randomly stretched
and colored creating much more variation. Planets are created in a similar way.
The final product is achieved using a basic Painter’s Algorithm.

## Images of the game
<table>
    <tr>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/ex1.png?raw=true" alt="example" title="Example 1" width="350" />
        </td>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/ex2.png?raw=true" alt="example" title="Mayhem version" width="350" />
        </td>
    </tr>
    <tr>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/ex3.png?raw=true" alt="example" title="Missile enemies" width="350" />
        </td>
        <td>
            <img src="https://github.com/KagonKhan/SpaceRanger/blob/master/examples/ex4.png?raw=true" alt="example" title="Aiming enemies" width="350" />
        </td>
    </tr>
</table>

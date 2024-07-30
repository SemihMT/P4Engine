# P4Engine

Welcome to the **P4Engine** repository! This project comprises two main components: a game engine (P4Engine) written in modern C++ and a recreation of the classic Bubble Bobble game. The engine provides a foundation upon which developers can build their own game systems, leveraging a variety of features and adhering to modern C++ core guidelines.

Disclaimer: This project was created using the [Minigin Template](https://github.com/avadae/minigin) for the course Programming 4 at Digital Arts & Entertainment.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Bubble Bobble Game](#bubble-bobble-game)
- [PPMEdit](#ppmedit)

## Overview

The **P4Engine** is a static library game engine designed with modern C++ practices in mind. Inspired by the book "Game Programming Patterns," it incorporates various design patterns to offer flexibility and extendibility. This repository includes both the game engine and a recreation of Bubble Bobble, showcasing the engine's capabilities and providing a template for your own game development projects.

## Features

The P4Engine offers a basic set of features to give developers the freedom to build their own systems:

- **Scene Manager**: Manage different scenes within your game.
- **Renderer**: A rendering system for drawing graphics.
- **Service Locator**: A pattern to manage global access to services, with support for creating custom services.
- **Singleton Base Class**: Simplify the creation of singleton classes (use with caution).
- **Time Manager**: A singleton class for easy access to frame times and total time.
- **Input Manager**: Support for XInput, facilitating game controller input.
- **Resource Manager**: Manage fonts and textures efficiently.
- **GameObject Base Class**: A foundational class for all game objects.
- **Component Base Class**: A base class for creating modular components that can be attached to game objects.


## Bubble Bobble Game

This repository includes a recreation of the classic Bubble Bobble game, built using P4Engine. The game demonstrates the engine's capabilities and serves as a practical example of its features. The game supports loading custom levels via PPM files.

### Game Modes
<img width="384" alt="BubbleBobble Game Mode selection" src="https://github.com/user-attachments/assets/a4cccc6f-94c4-4857-8add-b0f4b8bbaf2e">

#

**Singleplayer Mode**: Enjoy the classic Bubble Bobble gameplay on your own.

<img width="384" alt="BubbleBobble Single Player Mode" src="https://github.com/user-attachments/assets/19992870-d942-48f5-b689-2ed9d4b86bf6">

#

**Co-op Mode**: Team up with a friend to tackle levels together.

<img width="384" alt="BubbleBobble Co-Op Mode" src="https://github.com/user-attachments/assets/e5663887-8f76-4c4b-8121-e0217997cbef">

#
  
**Versus Mode**: Compete against a friend in PvP mode where one player controls an enemy, changing the dynamic to a player versus player game.

<img width="384" alt="BubbleBobble Versus Mode" src="https://github.com/user-attachments/assets/c1cb61f9-9c48-4bb4-8360-f66f99953624">

#

### Custom Levels

To create and load custom levels, use the PPMEdit tool available in the [PPMEdit repository](https://github.com/SemihMT/PPMEdit). This tool allows you to design levels with metadata for game tiles.

## PPMEdit

PPMEdit is a custom tool developed alongside P4Engine for creating and editing PPM files used in Bubble Bobble. It provides a user-friendly interface to design levels and add metadata to pixels, representing different game tiles.

For more information, visit the [PPMEdit repository](https://github.com/SemihMT/PPMEdit).

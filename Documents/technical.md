### Technical Specification: Cyber Fighters

- [Technical Specification: Cyber Fighters](#technical-specification-cyber-fighters)
  - [1. Title and Introduction](#1-title-and-introduction)
  - [2. Scope](#2-scope)
  - [3. Stakeholders](#3-stakeholders)
  - [4. Functional Requirements](#4-functional-requirements)
  - [5. Non-Functional Requirements](#5-non-functional-requirements)
  - [6. Architecture and Design](#6-architecture-and-design)
  - [7. Data Model](#7-data-model)
  - [8. User Interface Design](#8-user-interface-design)
  - [9. Development Environment](#9-development-environment)
  - [10. Maintenance and Support](#10-maintenance-and-support)
  - [11. Documentation](#11-documentation)


#### 1. Title and Introduction
- **Title**: Technical Specification for Cyber Fighters
- **Introduction**: This document outlines the technical details and requirements for the development of Cyber Fighters, a 1v1 combat game set in a cyberpunk universe.

#### 2. Scope
- **Scope**: Cyber Fighters aims to deliver an immersive gaming experience with pixel art visuals, intense combat mechanics, and dynamic background music. The scope includes developing core gameplay features, implementing character selection, map selection, and menu navigation functionalities.

#### 3. Stakeholders
- **Stakeholders**: 
  - Developers
    - Michel RIFF
    - Camille GAYAT
  - Project Managers
    - Camille GAYAT
  - Players


#### 4. Functional Requirements
- **Game**:
  - A map with unique backgrounds.
  - Characters with individual HP bars (range: 0-100).
  - Potential future implementation of a single-player mode against AI opponents.
- **Music**:
  - Unique background music for the map and menu.
- **Menu**:
  - Entrance phase requiring the 'Enter' key press to initiate the game.
  - Character selection phase.

#### 5. Non-Functional Requirements
- **Performance**: Ensure smooth gameplay experience with minimal lag.
- **Usability**: Create an intuitive user interface for seamless navigation.

#### 6. Architecture and Design
- **Architecture**: 
  - Modular design with components for gameplay, UI, and audio.
- **Design Patterns**: 
  - Implement MVC (Model-View-Controller) architecture for separation of concerns.
- **Technologies**: 
  - C++ for core game logic.


#### 7. Data Model
- **Data Entities**: 
  - Player (Attributes: name, HP).
  - Map (Attributes: name, background image, audio).
- **Data Storage**: 
  - Store player data locally during gameplay.

#### 8. User Interface Design
- **UI Elements**:
  - Main menu with buttons for character selection
  - In-game HUD displaying HP bars and other relevant information.

#### 9. Development Environment
- **Programming Languages**: 
  - C++ for game logic.
- **Development Tools**: 
  - IDE (Integrated Development Environment) such as Visual Code Studio.
- **Version Control**: 
  - Git for source code management.
- **Collaboration Tools**: 
  - Slack for team communication.


#### 10. Maintenance and Support
- **Maintenance Activities**: 
  - Regular updates for bug fixes and performance improvements.
- **Support Channels**: 
  - Online forums for user support such as Github.
- **Roles**: 
  - Developers responsible for maintenance tasks.

#### 11. Documentation
- **Functional Specification**: 
  - Game controls and mechanics.
- **Readme**: 
  - Installation instructions for developers.

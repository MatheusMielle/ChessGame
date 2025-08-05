# ChessGame

This project represents the evolution of a chess game implementation across three different technological paradigms, showcasing progression from basic console programming to modern web development.

**Project Evolution Timeline:**
- **Version 1 (2021):** Console-based local game - CS171 Final Project
- **Version 2 (2023):** Networked multiplayer game - CS313 Enhancement  
- **Version 3 (2025):** Modern web application - Personal Development

---

## Version 3 (In Development - 2025)
### Modern Web Application with React Frontend and C++ Backend

**Developer:** Matheus Mielle Silva  
**Development Status:** In Progress  
**Target Completion:** 2025

### Overview
A modern web-based chess game featuring a React frontend and C++ RESTful API backend, designed for enhanced user experience and performance.

### Features
1. **Modern Web Frontend:** React-based user interface with responsive design
2. **RESTful API Backend:** C++ backend providing game logic through HTTP API
3. **Real-time Updates:** WebSocket integration for live game state synchronization
4. **Enhanced User Experience:** Modern UI/UX with interactive chess board
5. **Scalable Architecture:** Microservices-based design for better maintainability
6. **Cross-platform Compatibility:** Web-based solution accessible from any modern browser

### Technical Implementation
- **Frontend:** React.ts with modern TypeScript (ES6+)
- **Backend:** C++ RESTful API server with HTTP endpoints
- **Communication:** HTTP/HTTPS for API calls, WebSockets for real-time updates
- **Architecture:** Single Page Application (SPA) with responsive design
- **Deployment:** Cloud-ready with containerization support
- **Database:** Potential integration for game history and user management

### Design Philosophy
- **Modern Web Standards:** Leveraging React.js for component-based, maintainable frontend development
- **API-First Approach:** C++ backend exposing RESTful endpoints for clean separation of concerns
- **Responsive Design:** Mobile-first approach ensuring accessibility across all device types
- **Performance Optimization:** C++ backend for high-performance game logic computation
- **Scalable Architecture:** Microservices design pattern for future feature expansion
- **Developer Experience:** Modern tooling and development practices for enhanced productivity

### Project Structure
```
Version 3/
├── frontend/                    # React.js application
│   ├── public/
│   │   ├── index.html          # Main HTML template
│   │   └── favicon.ico         # Site icon
│   ├── src/
│   │   ├── components/
│   │   │   ├── ChessBoard.jsx  # Interactive chess board component
│   │   │   ├── GameStatus.jsx  # Game state display
│   │   │   └── PlayerInfo.jsx  # Player information panel
│   │   ├── services/
│   │   │   ├── api.js          # Backend API communication
│   │   │   └── websocket.js    # Real-time communication
│   │   ├── styles/
│   │   │   └── components.css  # Component styling
│   │   ├── App.jsx             # Main application component
│   │   └── index.js            # Application entry point
│   ├── package.json            # Node.js dependencies
│   ├── webpack.config.js       # Build configuration
│   └── Dockerfile              # Container configuration
├── backend/                     # C++ API server
│   ├── src/
│   │   ├── api/
│   │   │   ├── routes.cpp      # HTTP endpoint definitions
│   │   │   └── websocket.cpp   # WebSocket handlers
│   │   ├── game/
│   │   │   ├── chess_engine.cpp # Core game logic
│   │   │   ├── board.cpp       # Board representation
│   │   │   └── pieces.cpp      # Piece movement logic
│   │   ├── utils/
│   │   │   ├── json.cpp        # JSON parsing utilities
│   │   │   └── validation.cpp  # Input validation
│   │   └── main.cpp            # Server entry point
│   ├── headers/
│   │   ├── chess_engine.h      # Game logic declarations
│   │   ├── api.h               # API interface definitions
│   │   └── types.h             # Common type definitions
│   ├── CMakeLists.txt          # Build configuration
│   └── Dockerfile              # Container configuration
├── docker-compose.yml          # Multi-container orchestration
└── README.md                   # Version 3 documentation
```

### How to Run
1. **Development Setup:**
   - Navigate to `Version 3/backend/`
   - Run `cmake . && make` to build the C++ API server
   - Start the backend server on the configured port
   
2. **Frontend Development:**
   - Navigate to `Version 3/frontend/`
   - Run `npm install` to install dependencies
   - Run `npm start` for development mode with hot reloading
   
3. **Production Deployment:**
   - Run `docker-compose up` to start both frontend and backend containers
   - Access the application through the web browser
   - API endpoints available for integration testing

### Dependencies
- **C++ Backend:**
  - `#include <httplib>` - HTTP server library for RESTful API
  - `#include <nlohmann/json>` - Modern JSON parsing and generation
  - `#include <websocketpp>` - WebSocket protocol implementation
  - `#include <thread>` - Multi-threading for concurrent connections
  - `CMake` - Modern build system
  - `Docker` - Containerization for deployment

- **React Frontend:**
  - `React 18+` - Modern component-based UI framework
  - `axios` - HTTP client for API communication
  - `socket.io-client` - WebSocket client for real-time updates
  - `styled-components` - CSS-in-JS styling solution
  - `webpack` - Module bundler and build tool
  - `npm/yarn` - Package management
  - `ESLint & Prettier` - Code quality and formatting tools

### Planned Improvements
- Comprehensive input validation with user-friendly error messages
- Advanced game state management with undo/redo functionality
- Enhanced chess rules implementation including castling, en passant, and pawn promotion
- Real-time game analytics and move suggestions

---

## Version 2 (CS313 - December 2023)
### Networked Chess Game with Client-Server Architecture

**Developers:** Matheus Mielle Silva, Fabian Gomez, Bereket Lemma, and Lex Sinclair  
**Course:** CS313 (Computer Networks) - Whitworth University  
**Completed:** December 2nd, 2023

### Overview
A networked chess game with client-server architecture and web interface for remote multiplayer gameplay, building upon the original console game.

### Features
1. **Network Multiplayer:** Client-server architecture allowing remote gameplay
2. **Web Interface:** Flask-based web application for game distribution
3. **Socket Communication:** Real-time communication between players using TCP sockets
4. **Cross-platform Support:** Separate client and server executables
5. **Enhanced Architecture:** Improved code organization and networking capabilities

### Technical Implementation
- **Server:** C++ with socket programming (Port 50001)
- **Client:** C++ client application with socket communication
- **Web Interface:** Python Flask application for game distribution
- **Communication:** TCP socket-based networking
- **Deployment:** Web server hosting for client download and game access

### Design Evolution
- **Client-Server Architecture:** Separation of game logic and user interface for network play
- **Socket Programming:** TCP sockets for reliable real-time communication
- **Web Distribution:** Flask web application for easy client access and download
- **Modular Design:** Enhanced code organization with proper separation of concerns

### Project Structure
```
Version 2/
├── Socket.h                     # Socket wrapper for cross-platform networking
├── Client/
│   ├── bin/
│   │   └── main.exe            # Client executable
│   └── source/
│       └── Player_main.cpp     # Client application
├── Server/
│   ├── bin/
│   │   └── main.exe            # Server executable
│   └── source/
│       ├── checkers.cpp        # Game logic
│       └── main.cpp            # Server application
└── Site/
    ├── main.py                 # Flask web application
    ├── static/
    │   ├── chess.exe           # Game resources
    │   ├── chess.jpg           # UI assets
    │   ├── Client.zip          # Downloadable client
    │   ├── main.exe            # Additional executables
    │   └── style.css           # Web styling
    └── templates/
        └── page.html           # Web interface template
```

### How to Run
1. **Server Setup:**
   - Navigate to `Version 2/Server/bin/`
   - Run `main.exe` to start the server (Port 50001)
   
2. **Client Connection:**
   - Navigate to `Version 2/Client/bin/`
   - Run `main.exe` to connect to the server
   
3. **Web Interface (Optional):**
   - Navigate to `Version 2/Site/`
   - Run `python main.py` to start the Flask web server
   - Access via web browser for client download

### Dependencies
- **C++ Server/Client:**
  - `#include <thread>` - Multi-threading support
  - `#include <chrono>` - Time utilities
  - Custom `Socket.h` - Cross-platform socket wrapper
  - Windows: `-lws2_32` linking flag for Winsock

- **Python Web Interface:**
  - `Flask` - Web framework for client distribution
  - `render_template` - Template rendering
  - `send_file` - File download functionality

### Enhancements from Version 1
- Improved network error handling and connection management
- Better input validation and user experience
- Enhanced game state synchronization between client and server

---

## Version 1 (CS171 - December 2021)
### Local Console-Based Chess Game

**Developers:** Matheus Mielle Silva and Fabian Gomez  
**Course:** CS171 (Computer Science I) - Whitworth University  
**Completed:** December 16th, 2021

### Overview
The original console-based chess game for two players on the same computer, created as a final project for Computer Science I.

### Features
1. **Local Gameplay:** Console-based chess game for two players on the same computer
2. **Turn-based System:** Players alternate turns choosing pieces and destinations
3. **Piece Movement Validation:** Each piece follows proper chess movement rules
4. **Basic Game Logic:** Handles piece capture and basic win conditions
5. **Error Handling:** Validates user input and handles invalid moves

### Technical Implementation
- **Language:** C++
- **Architecture:** Function-based design with modular headers
- **Data Structure:** 3D array to represent the chessboard with piece positions and colors
- **Input/Output:** Console-based interface with coordinate input system
- **Compilation:** Standard C++ compilation with custom headers

### Design Rationale
- **Function-based Architecture:** Used functions instead of classes for simplicity and team familiarity
- **3D Array Structure:** Stores piece information, positions, and colors in a compact, organized format
- **Individual Piece Functions:** Each piece type has its own function for good modularization
- **Conditional Logic:** Extensive use of if statements to handle piece movement directions
- **Hybrid Loop Structure:** Combination of do-while and for loops for movement validation

### Project Structure
```
Version 1/
├── bin/
│   └── main.exe                 # Compiled executable
├── headers/
│   ├── assign_boards.h          # Board initialization
│   ├── checkers.h               # Move validation
│   ├── get_funcs.h              # Input handling
│   ├── print.h                  # Display functions
│   └── swap.h                   # Piece movement
└── source/
    ├── assign_boards.cpp        # Board setup implementation
    ├── checkers.cpp             # Movement validation logic
    ├── get_funcs.cpp            # Input processing
    ├── main.cpp                 # Main game loop
    ├── print.cpp                # Display functionality
    └── swap.cpp                 # Piece swapping logic
```

### How to Run
1. Navigate to `Version 1/bin/`
2. Run `main.exe`
3. Follow console prompts for piece selection and movement

### Dependencies
- `#include <iostream>` - Standard input/output
- `#include <cctype>` - Character classification
- `#include <string.h>` - String manipulation
- Custom headers: `checkers.h`, `assign_boards.h`, `swap.h`, `print.h`, `get_funcs.h`
- `using namespace std;`

### Known Limitations
- Input validation is limited - entering values outside the valid range (1-8 for numbers, A-H for letters) may cause undefined behavior
- Path blocking detection may not work perfectly in all scenarios
- User input errors for piece selection or destination coordinates need careful handling
- Attempting to move one player's piece to a square occupied by another of their own pieces

---

## Common Game Rules and Behavior

All versions implement core chess functionality:
- **Piece Movement:** Each piece (pawn, rook, bishop, knight, queen, king) follows standard chess movement rules
- **Turn Management:** Players alternate turns with proper validation
- **Piece Capture:** Eliminated pieces are removed from the board
- **Input Validation:** System handles invalid moves and out-of-bounds input
- **Win Conditions:** Game ends when a king is captured or after excessive invalid moves

## License and Copyright

**License:** Only project developers are allowed to edit or share this file electronically unless such permission is given by the developers.

**Copyright:**
- (C) Matheus M Silva 2021-2025
- (C) Fabian Gomez 2021-2023
- (C) Bereket Lemma 2023
- (C) Lex Sinclair 2023

## References and Acknowledgments

### External References
- **Chess Rules:** [Wholesale Chess - How Chess Pieces Move](https://www.wholesalechess.com/pages/new-to-chess/pieces.html)
- **Special Thanks:** Andre East (Whitworth University CS II student) for brainstorming individual piece function design

### Academic Context
- **Original Course:** CS171 (Computer Science I) - Whitworth University
- **Enhanced Course:** CS313 (Computer Networks) - Whitworth University  
- **Current Development:** Personal Project (2025) - Modern Web Development

### Learning Objectives Achieved
- Object-oriented programming concepts
- Network programming and socket communication
- Client-server architecture design
- Web application development
- Modern frontend frameworks (React.js)
- RESTful API design and implementation
- Containerization and deployment strategies
- Software project evolution and enhancement

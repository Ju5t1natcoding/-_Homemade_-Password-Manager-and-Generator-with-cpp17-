# 🔐 Homemade Password Manager & Generator

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)](https://github.com/Ju5t1natcoding/-_Homemade_-Password-Manager-and-Generator-with-cpp17-)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![CodeBlocks](https://img.shields.io/badge/IDE-CodeBlocks%2020.03-orange)](http://www.codeblocks.org/)

A secure, lightweight console-based password manager and generator built with modern C++17 features. This portfolio project demonstrates advanced C++ programming concepts while providing a practical tool for password management.

## ✨ Features

### 🔑 Password Generation
- **Customizable complexity**: Configure length, character sets, and complexity requirements
- **Multiple character sets**: Letters (upper/lower case), numbers, special characters
- **Secure randomization**: Uses cryptographically secure random number generation
- **Batch generation**: Generate multiple passwords at once

### 🗃️ Password Management
- **Secure storage**: Encrypted local database for password storage
- **Organized categories**: Group passwords by service type or custom categories
- **Advanced search**: Quick search and filtering capabilities
- **Import/Export**: Backup and restore functionality

### 🛡️ Security Features
- **AES-256 encryption**: Optional advanced encryption with Crypto++ library
- **Master password protection**: Single master password to access all stored data
- **Secure hashing**: Industry-standard password hashing algorithms
- **Memory protection**: Secure memory handling to prevent data leaks

### 💻 User Interface
- **Console-based**: Lightweight, fast, and resource-efficient
- **Intuitive menus**: Easy-to-navigate command-line interface
- **Cross-platform**: Compatible with Windows, Linux, and macOS

## 🏗️ Architecture

This project showcases several advanced C++17 features:
- Smart pointers for memory management
- STL containers and algorithms
- Exception handling
- Object-oriented design patterns
- Template programming
- File I/O operations

## 🚀 Quick Start

### Prerequisites

- **C++17 compatible compiler** (GCC 7+, Clang 5+, MSVC 2017+)
- **CodeBlocks IDE 20.03** (recommended) or any C++ IDE
- **Crypto++** library (optional, for AES-256 encryption)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Ju5t1natcoding/-_Homemade_-Password-Manager-and-Generator-with-cpp17-.git
   cd -_Homemade_-Password-Manager-and-Generator-with-cpp17-
   ```

2. **Compile the project**
   
   **Option A: Using CodeBlocks**
   - Open the project in CodeBlocks IDE
   - Include all `.cpp` and `.h` files (ignore `.cbp` if problematic)
   - Build and run the project

   **Option B: Using GCC**
   ```bash
   g++ -std=c++17 -O2 -o password_manager *.cpp
   ./password_manager
   ```

   **Option C: Using CMake** (if CMakeLists.txt is available)
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ./password_manager
   ```

### Optional: Enable AES-256 Encryption

To use advanced AES-256 encryption:

1. **Install Crypto++ library**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install libcrypto++-dev
   
   # CentOS/RHEL
   sudo yum install cryptopp-devel
   
   # macOS (Homebrew)
   brew install cryptopp
   
   # Windows (vcpkg)
   vcpkg install cryptopp:x64-windows
   ```

2. **Uncomment AES-256 code sections**
   - Look for `// AES-256` comments in the source code
   - Uncomment the relevant encryption/decryption functions
   - Add necessary `#include <cryptopp/...>` headers

3. **Recompile with Crypto++ support**
   ```bash
   g++ -std=c++17 -O2 -o password_manager *.cpp -lcryptopp
   ```

## 📖 Usage Guide

### First Launch
1. Run the executable: `./password_manager`
2. Set up your master password (choose a strong, memorable password)
3. The application will create a secure database file

### Main Menu Options
*Note: The current interface is in Romanian, with English support planned for future releases.*

- **Generate Password**: Create secure passwords with custom parameters
- **Add Password**: Store new passwords with associated metadata
- **View Passwords**: Browse your stored passwords (requires master password)
- **Search**: Find specific passwords by service name or username
- **Delete Password**: Remove outdated or unwanted entries
- **Export/Import**: Backup or restore your password database

### Password Generation Example
```
Choose password length: 16
Include uppercase letters? (y/n): y
Include numbers? (y/n): y
Include special characters? (y/n): y
Generated password: Kj9$mP2!nR7&qL3@
```

### Security Best Practices
- Use a unique, strong master password
- Enable AES-256 encryption for sensitive data
- Regularly backup your encrypted database
- Never share your master password
- Keep the application and dependencies updated

## 📂 Project Structure

```
├── src/
│   ├── main.cpp                 # Application entry point
│   ├── PasswordManager.h        # Core manager class header
│   ├── PasswordManager.cpp      # Manager implementation
│   ├── PasswordGenerator.h      # Generator class header
│   ├── PasswordGenerator.cpp    # Generator implementation
│   ├── Encryption.h             # Encryption utilities header
│   ├── Encryption.cpp           # Encryption implementation
│   ├── Utils.h                  # Helper functions header
│   └── Utils.cpp                # Utilities implementation
├── docs/                        # Documentation files
├── tests/                       # Unit tests (if available)
├── README.md                    # This file
└── LICENSE                      # Project license
```

## 🔧 Configuration

### Customizing Settings
Edit the configuration constants in the source files:

- **Default password length**: Modify in `PasswordGenerator.cpp`
- **Character sets**: Customize in generator class
- **File paths**: Update storage locations in `PasswordManager.cpp`
- **Encryption settings**: Configure in `Encryption.cpp`

### Adding Custom Features
1. Extend the `PasswordManager` class for new functionality
2. Implement additional methods in respective source files
3. Update the main menu in `main.cpp`
4. Follow the existing code style and patterns

## 🛠️ Development

### Building for Development
```bash
# Debug build with symbols
g++ -std=c++17 -g -Wall -Wextra -o password_manager_debug *.cpp

# Release build with optimizations
g++ -std=c++17 -O3 -DNDEBUG -o password_manager_release *.cpp
```

### Code Style Guidelines
- Follow modern C++17 best practices
- Use meaningful variable and function names
- Add comprehensive comments for complex algorithms
- Implement proper error handling
- Use RAII principles for resource management

### Testing
- Test all password generation scenarios
- Verify encryption/decryption functionality
- Test database operations (add, search, delete)
- Validate input handling and edge cases

## 🚧 Roadmap

### Planned Features
- [ ] **English language interface** - Complete UI translation
- [ ] **Graphical User Interface** - Qt or GTK-based GUI
- [ ] **Cloud synchronization** - Secure cloud backup options
- [ ] **Two-factor authentication** - Additional security layer
- [ ] **Browser integration** - Browser extension for auto-fill
- [ ] **Mobile companion** - Android/iOS companion app
- [ ] **Password strength analyzer** - Built-in password assessment
- [ ] **Secure sharing** - Share passwords with trusted contacts

### Known Limitations
- Interface currently only in Romanian
- Console-based interface only
- Local storage only (no cloud sync)
- AES-256 requires external library

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### How to Contribute
1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Contribution Guidelines
- Write clean, well-documented code
- Follow existing code style and patterns
- Add unit tests for new features
- Update documentation as needed
- Ensure cross-platform compatibility

### Areas for Contribution
- English language translation
- Additional encryption algorithms
- GUI development
- Unit test implementation
- Performance optimizations
- Security enhancements

## 📋 Requirements

### Minimum Requirements
- C++17 compatible compiler
- 50MB available disk space
- Command-line interface support

### Recommended Requirements
- Modern C++ IDE (CodeBlocks, Visual Studio, CLion)
- Crypto++ library for enhanced security
- Version control system (Git)

## 🔒 Security Considerations

### Security Features
- **Encryption at rest**: All stored passwords are encrypted
- **Secure memory handling**: Sensitive data cleared from memory
- **Master password hashing**: Uses secure hashing algorithms
- **No network communication**: Fully offline operation

### Security Limitations
- Master password stored locally (user responsibility)
- Console interface may log commands in shell history
- Backup files should be securely stored

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Ju5t1natcoding**
- GitHub: [@Ju5t1natcoding](https://github.com/Ju5t1natcoding)
- Portfolio Project: C++17 Password Manager
- LinkedIn: [Connect with me](https://linkedin.com/in/yourprofile) <!-- Add your LinkedIn -->

## 🙏 Acknowledgments

- **Crypto++** library for advanced encryption capabilities
- **C++17 standard** for modern language features
- **CodeBlocks IDE** for development environment
- Open source community for inspiration and best practices

## 📞 Support & Contact

### Getting Help
- **Documentation**: Check this README and inline code comments
- **Issues**: [Open an issue](https://github.com/Ju5t1natcoding/-_Homemade_-Password-Manager-and-Generator-with-cpp17-/issues) for bugs or feature requests
- **Discussions**: Use GitHub Discussions for questions and ideas

### Reporting Issues
When reporting issues, please include:
- Operating system and version
- Compiler version and type
- Steps to reproduce the issue
- Expected vs actual behavior
- Any error messages or logs

---

**⭐ Star this repository if you find it helpful! ⭐**

*This project is part of my software development portfolio, showcasing modern C++ programming skills and security-focused application design.*

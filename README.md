# myteams

This is a Microsoft teams like communication tool written entirely in C, this is a CLI tool that's separated between a client and a server binary.

This tool supports individual users logging in and out, private messages between users, there is a saving system so that everything gets saved by itself when the server gets shut down and loaded back when it turns back on, and there is also a safety mechanism that prevents corrupted save files from being loaded.

## Building

### Requirements
- [gcc](https://gcc.gnu.org/)

Just type ``make`` in a shell at the root of the repo

## Usage

### Server
```bash
./myteams_server [port]
```

### Client
```bash
./myteams_cli [ip] [port]
```

## Demo

https://github.com/user-attachments/assets/daa4f134-dcc8-468e-8ff7-185b17a04c80

### Available commands for the client:

| Command                              | Action                                              |
|--------------------------------------|-----------------------------------------------------|
| /help                                | show help                                           |
| /login [“user_name”]                 | set the user_name used by client                    |
| /logout                              | disconnect the client from the server               |
| /users                               | get the list of all users that exist on the domain  |
| /user [“user_uuid”]                  | get details about the requested user                |
| /send [“user_uuid”] [“message_body”] | send a message to specific user                     |
| /messages [“user_uuid”]              | list all messages exchanged with the specified user |

## The saving system in action

https://github.com/user-attachments/assets/d1b1bd8d-7e14-45b7-956c-db5517992cbe

## A look at the corruption-prevention mechanism in action

> To the left is the server's save file opened in a hex editor. In this example, I've changed a single bit to mimick data corruption

https://github.com/user-attachments/assets/5b39a649-afa1-49eb-bafe-5072adc91c03



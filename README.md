# HTTP-Cerver
HTTP server in C

```
mi_servidor_http/
├── bin/                # Aquí se guardará el programa ejecutable final
├── src/                # Archivos de código fuente (.c)
│   ├── main.c          # Orquestador principal
│   ├── server.c        # Gestión de sockets y red
│   ├── parser.c        # Análisis de peticiones HTTP
│   └── utils.c         # Funciones de ayuda (logs, manejo de errores)
├── include/            # Archivos de cabecera (.h)
│   ├── server.h
│   ├── parser.h
│   └── utils.h
├── public/             # Tu carpeta web (HTML, CSS, JS)
│   └── index.html
└── Makefile            # El "script" para compilar todo automáticamente
```

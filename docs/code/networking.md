# Networking (cnet.h)
## Networking functions
## note: include SDL2_net documentation because the available one is outdated

# **types**:


# **enumerations**:
* HTTP_ERR_NONE   = 0,
* HTTP_ERR_URL    = 1,
* HTTP_ERR_HOST   = 2,
* HTTP_ERR_SOCKET = 3,
* HTTP_ERR_DATA   = 4,
* HTTP_ERR_NOFILE = 5,

# **constants**:


# **functions**:
## categories:
### **general**:
* **void net_init(void)**
* **void net_finish(void)**

* **void net_set_server(bool server)**
* **bool net_is_server(void)**
* **bool net_is_client(void)**
### **HTTP**:


* **int net_http_get(char\* out, int max, char\* fmt, ...)**
* **int net_http_upload(const char\* filename, char\* fmt, ...)**

# **SDL2_net documentation**
## should be a much more complete than the rest of the engine
# **types**:
* **SDLNet_version**
* **IPaddress**
* **SDLNet_GenericSocket**
* **TCPsocket**
* **UDPsocket**
* **UDPpacket**
* **SDLNet_SocketSet**

# **constants/macros**:
* SDL_NET_MAJOR_VERSION   
* SDL_NET_MINOR_VERSION   
* SDL_NET_PATCHLEVEL      
* INADDR_ANY = 0x00000000
* INADDR_NONE = 0xFFFFFFFF
* INADDR_LOOPBACK = 0x7f000001
* INADDR_BROADCAST = 0xFFFFFFFF
* SDLNET_MAX_UDPCHANNELS  32
* SDLNET_MAX_UDPADDRESSES 4
# **functions**:
## categories:
### **version detection**
* ### **void SDL_NET_VERSION(SDLNet_version X)**
    #### fill SDLNet_version structure with **included** SDLNet version data

* ### **const SDLNet_version \* SDLNet_Linked_Version(void)**
    #### get SDLNet_version structure with **dynamically linked** SDLNet version data

### **initalization/shutdown**:
* ### **int SDLNet_Init(void)**
    #### load dynamic library and initialize networking, must be called before any SDLNet call and after SDL_init. 
    **return:** 0 on success and -1 on fail

* ### **void SDLNet_Quit(void)**:
    #### unload dynamic library, close all sockets and cleanup networking API

### **ipv4**

* ### **const char \*   SDLNet_ResolveIP(const IPaddress \*ip)**
    #### resolve IP into a hostname
    #### **parameters**
    - ip - IPaddress pointer to resolve
    #### **return:** hostname on success (host.domain.ext). NULL on errors, such as when it's unable to resolve. The returned pointer is not to be freed. Each call the pointer's data will change to the new value, you have to copy it to keep it. 
    #### **example**:
    ```c
    IPaddress addr;
    //do something...
    char * temp = SDLNet_ResolveIP(&addr);

    char * hostname = malloc(strlen(temp));
    strcpy(hostname, temp);//hostname won't change now
    ```

* ### **int SDLNet_ResolveHost(IPaddress \*address, const char \*host, Uint16 port)**
    #### resolve hostname into an IP
    #### **parameters**:
    - address - IPaddress pointer to fill data, must be allocated
    - host - hostname to resolve, NULL if hosting a server
    - port - port server will listening, can be 0 if just doing DNS resolutions
    #### **return**: 0 on success, -1 & host will be INADDR_NONE on error
    #### **example**:
    ```c
    IPaddress addr;
    SDLNet_ResolveHost(&addr, "github.com", 80);
    //connect or do something...
    ```

* ### **int SDLNet_GetLocalAddresses(IPaddress \*addresses, int maxcount)**
    #### get local network addresses
    #### **parameters**
    - addresses - address array to store, should be already allocated
    - maxcount - maximum addresses to search
    #### **return**: found addresses count
    #### **example**:
    ```c
    IPaddress local[16];
    int count = SDLNet_GetLocalAddresses(local, 16);
    // do something...
    ```

### **TCP**

* ### **TCPsocket   SDLNet_TCP_Open(IPaddress \*ip)**
    #### creates a TCP connection
    #### **parameters**
    - ip - address to connect
    #### **return** a valid TCPsocket on success, NULL on error
    #### **example**
    ```c 
    if(is_server){
        IPaddress addr;
        SDLNet_ResolveHost(&addr, NULL, 9999);
        //open server socket on port 9999
        TCPsocket server = SDLNet_TCP_Open(&addr);
    }else{
        IPaddress addr;
        SDLNet_ResolveHost(&addr, "127.0.0.1", 9999);
        //connect client socket on port 9999
        TCPsocket client = SDLNet_TCP_Open(&addr);
    }
    ```

* ### **void   SDLNet_TCP_Close(TCPsocket sock)**
    #### close TCP connection
    #### **parameters**:
    - sock - socket to close
    #### **return**: an IPaddress. NULL on error or when sock is a server 
    #### **example**:
    ```c
    TCPsocket client;
    //connect and do stuff
    SDLNet_TCP_Close(client);
    ```

* ### **TCPsocket   SDLNet_TCP_Accept(TCPsocket server)**
    #### accept incoming connection
    #### **parameters**:
    - server - socket to connect
    #### **return**: connected socket, NULL if couldn't connect or there's no incoming connection.
    #### **example**
    ```c
    TCPsocket server, client;
    // connect server
    while(!client){
        client = SDLNet_TCP_Accept(server);
        //don't forget delaying to save resources
    }
    //client should be connected by now
    ```

* ### **IPaddress \*   SDLNet_TCP_GetPeerAddress(TCPsocket sock)**
    #### get ip address from the peer (other end)
    #### **parameters**:
    - sock - socket to get IP from the peer
    #### **return**: an IPaddress. NULL on error or when sock is a server 
    #### **example**:
    ```c
    TCPsocket server, client;
    // connect server and client...
    IPaddress client_addr = *SDLNet_TCP_GetPeerAddress(client);
    ```
* ### **int SDLNet_TCP_Send(TCPsocket sock, const void \*data, int len)**
    #### send data with size len over sock
    #### **parameters**:
    - sock - socket to send data
    - data - data to send
    - len - size
    #### **return**: number of bytes sent, if less than len some error ocurred or the peer disconnected
    #### **example**
    ```c
    TCPsocket server;
    //host server and connect with client
    char * message = "Hello client";

    int bytes = SDLNet_TCP_Send(client, message, strlen(message));
    if(bytes < strlen(message)){
        printf("error");
        //handle error
    }
    ```

* ### **int SDLNet_TCP_Recv(TCPsocket sock, void \*data, int maxlen)**
    #### receive data with size len over sock
    #### **parameters**:
    - sock - socket to receive data
    - data - where to store the data
    - maxlen - maximum size
    #### **return**: number of bytes received, if less or equal to zero some error ocurred or the peer disconnected
    #### **example**:
    ```c
    TCPsocket client;
    //do stuff and connect to the server
    char message[128];

    int bytes = SDLNet_TCP_Recv(client, message, 128);
    if(bytes <= 0){
        //handle error
    }
    printf("received message from server: %s", message);
    ```

### **UDP**

* **UDPpacket *   SDLNet_AllocPacket(int size)**


* **int   SDLNet_ResizePacket(UDPpacket \*packet, int newsize)**


* **void   SDLNet_FreePacket(UDPpacket \*packet)**



* **UDPpacket **   SDLNet_AllocPacketV(int howmany, int size)**



* **void   SDLNet_FreePacketV(UDPpacket \*\*packetV)**



* **UDPsocket   SDLNet_UDP_Open(Uint16 port)**



* **void   SDLNet_UDP_SetPacketLoss(UDPsocket sock, int percent)**



* **int   SDLNet_UDP_Bind(UDPsocket sock, int channel, const IPaddress \*address)**



* **void   SDLNet_UDP_Unbind(UDPsocket sock, int channel)**



* **IPaddress * SDLNet_UDP_GetPeerAddress(UDPsocket sock, int channel)**



* **int SDLNet_UDP_SendV(UDPsocket sock, UDPpacket \*\*packets, int npackets)**



* **int SDLNet_UDP_Send(UDPsocket sock, int channel, UDPpacket \*packet)**



* **int SDLNet_UDP_RecvV(UDPsocket sock, UDPpacket \*\*packets)**



* **int SDLNet_UDP_Recv(UDPsocket sock, UDPpacket \*packet)**



* **void SDLNet_UDP_Close(UDPsocket sock)**

### **socket set**:

## note: SDLNet_GenericSocket can be both TCP or UDP, if a function uses it, it has 2 more versions for each protocol

* ### **SDLNet_SocketSet SDLNet_AllocSocketSet(int maxsockets)**
    #### allocate a socket set
    #### **parameters**:
    - maxsockets - maximum socket number to watch
    #### **return**: new empty socket set, NULL on error, such as out of memory
    #### **example**:
    ```c
    SDLNet_SocketSet socket_set;
    socket_set = SDLNet_AllocSocketSet(int maxsockets);
    ```
* **void   SDLNet_FreeSocketSet(SDLNet_SocketSet set)**
    #### free a socket set
    #### **parameters**:
    - set - socket set to free
    #### **return**: new empty socket set, NULL on error, such as out of memory
    #### **example**:
    ```c
    SDLNet_SocketSet socket_set;
    socket_set = SDLNet_AllocSocketSet(int maxsockets);
    ```

* ### **int SDLNet_AddSocket(SDLNet_SocketSet set, SDLNet_GenericSocket sock)**
    #### add socket to watch in a socket set
    #### **parameters**:
    - set - socket set to add socket
    - sock - socket to add
    #### **return**: number of sockets on succes. -1 on errors.
    #### **example**:
    ```c
    SDLNet_SocketSet socket_set;
    socket_set = SDLNet_AllocSocketSet(int maxsockets);
    SDLNet_GenericSocket socket;
    //do something and connect
    int sockets = SDLNet_AddSocket(socket);
    if(sockets == -1){
        //handle error
    }
    ```



* ### **int SDLNet_DelSocket(SDLNet_SocketSet set, SDLNet_GenericSocket sock)**
    #### delete socket from socket set
    #### **parameters**:
    - set - socket set to delete from
    - sock - socket to delete
    #### **return**: number of sockets on success. -1 on errors.
    #### **example**:
    ```c
    SDLNet_SocketSet socket_set;
    SDLNet_GenericSocket socket;
    int sockets = SDLNet_AddSocket(socket);
    //do socket set stuff
    int success = 
    //
    ```

* ### **int SDLNet_CheckSockets(SDLNet_SocketSet set, Uint32 timeout)**
    #### check activity in a socket set, disconnecting or errors are also activities
    #### **parameters**:
    - set - socket set to check activity
    - timeout - time waiting for activity in ms, 0 = no wait, -1 = 49 days (softly, don't.)
    #### **return**: number of sockets with activity on success. -1 on errors or empty set
    #### **example**:
    ```c
    SDLNet_GenericSocket sockets[16];
    // connect and stuff
    SDLNet_SocketSet socket_set;
    // do socket set stuff

    while(running){
        int num_ready = SDLNet_CheckSockets(socket_set, 1000);
        if(num_ready > 0){
            //handle activity
        }
    }
    ```


* ### **int SDLNet_SocketReady(sock)**
    #### check activity in a socket, disconnecting or errors are also activities
    #### **parameters**:
    - sock - socket to check
    #### **return**: non-zero for activity. zero for no activity.
    #### **example**:
    ```c
    SDLNet_GenericSocket sockets[16];
    int sock_number = 16;
    SDLNet_SocketSet socket_set;
    // do socket set stuff
    while(running){
        int num_ready = SDLNet_CheckSockets(socket_set, 1000);
        if(num_ready > 0){
            for(int i=0;i<sock_number;i++){
                if(SDLNet_SocketReady(sockets[i])){
                    //handle it
                }
            }
        }
    }
    ```

### **errors**:

* ### **void SDLNet_SetError(const char \*fmt, ...)**
    #### set SDL_Net error string
* ### **const char * SDLNet_GetError(void)**
    #### get SDL_Net error string

### **endian**:

* ### **void SDLNet_Write16/32(Uint16/32 value, void \*areap)**
    #### write 16/32 bit value into the right endian
    #### **parameters**:
    - value - value to write
    - areap - area to write

* ### **Uint16/32 SDLNet_Read16/32(void \*areap)**
    #### read 16/32 bit value in the right endian
    #### **parameters**:
    - areap - area to read
    #### **return**: value in area in the right endian


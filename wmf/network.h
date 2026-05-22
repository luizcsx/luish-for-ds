#ifndef LUISH_WMF_NETWORK_H
#define LUISH_WMF_NETWORK_H

#define WIIMMFI_NAS_SERVER        "nas.wiimmfi.de"
#define WIIMMFI_MASTER_SERVER     "gamestats.wiimmfi.de"
#define WIIMMFI_HTTP_PORT         80
#define WIIMMFI_NAS_PORT          443

typedef enum {
    WMF_STATUS_DISCONNECTED = 0,
    WMF_STATUS_INIT_WIFI,
    WMF_STATUS_CONNECTING_AP,
    WMF_STATUS_CONNECTED_AP,
    WMF_STATUS_AUTHENTICATING,
    WMF_STATUS_READY,
    WMF_STATUS_ERROR
} WmfNetworkStatus;

typedef struct {
    WmfNetworkStatus status;
    unsigned int ip_address;
    unsigned int gateway;
    int socket_fd;
} LuishWmfConfig;
)
extern volatile LuishWmfConfig sys_wmf;

int wmf_inicializar_hardware(void);

WmfNetworkStatus wmf_conectar_ap(void);

int wmf_autenticar_sistema(const char* game_code);

void wmf_desconectar(void);

#endif // LUISH_WMF_NETWORK_H

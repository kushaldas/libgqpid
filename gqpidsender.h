
#include <glib.h>
#include <gqpidmessage.h>


typedef struct _GQpidSender GQpidSender;
#ifdef __cplusplus
GQpidSender*            g_qpid_sender_new                       (qpid::messaging::Session &, const gchar*);
extern "C" {
#endif
void                    g_qpid_sender_send                      (GQpidSender *, GQpidMessage  *);
#ifdef __cplusplus
}
#endif

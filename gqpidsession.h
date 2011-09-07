
#include <glib.h>
#include <gqpidreceiver.h>
#include <gqpidsender.h>

#ifdef __cplusplus
#include <qpid/messaging/Connection.h>
#endif

typedef struct _GQpidSession GQpidSession;
#ifdef __cplusplus
GQpidSession*           g_qpid_session_new  (qpid::messaging::Connection &);
extern "C" {
#endif

GQpidSender*            g_qpid_session_create_sender    (GQpidSession*, gchar*);
GQpidReceiver*          g_qpid_session_create_receiver  (GQpidSession*, gchar*);
gint                    g_qpid_session_get_receivable   (GQpidSession *);
void                    g_qpid_session_reject           (GQpidSession *, GQpidMessage *);
void                    g_qpid_session_acknowledge      (GQpidSession*);
void                    g_qpid_session_close            (GQpidSession*);
void                    g_qpid_session_free             (GQpidSession*);

#ifdef __cplusplus
}
#endif

#include "./qstm_types.h"


bool ___registerMetaType()
{
    return true;
}

const QHash<int, QString> ___QStmProtocolName(){
    QHash<int, QString> r;
    r.insert(TcpSocket , QT_STRINGIFY2(tcpsocket));
    r.insert(UdpSocket , QT_STRINGIFY2(udpsocket));
    r.insert(WebSocket , QT_STRINGIFY2(websocket));
    r.insert(Mqtt      , QT_STRINGIFY2(mqtt)     );
    r.insert(Amqp      , QT_STRINGIFY2(amqp)     );
    r.insert(Http      , QT_STRINGIFY2(http)     );
    r.insert(Https     , QT_STRINGIFY2(https)    );
    return r;
}

const QHash<QString, int> ___QStmProtocolType(){
    QHash<QString,int> r;

    r.insert(QT_STRINGIFY2(TcpSocket),TcpSocket  );
    r.insert(QT_STRINGIFY2(UdpSocket),UdpSocket  );
    r.insert(QT_STRINGIFY2(WebSocket),WebSocket  );
    r.insert(QT_STRINGIFY2(Mqtt)     ,Mqtt       );
    r.insert(QT_STRINGIFY2(Amqp)     ,Amqp       );
    r.insert(QT_STRINGIFY2(Http)     ,Http       );
    r.insert(QT_STRINGIFY2(Https)    ,Https      );

    r.insert(QT_STRINGIFY2(tcp)      ,TcpSocket  );
    r.insert(QT_STRINGIFY2(udp)      ,UdpSocket  );
    r.insert(QT_STRINGIFY2(wss)      ,WebSocket  );
    r.insert(QT_STRINGIFY2(mqtt)     ,Mqtt       );
    r.insert(QT_STRINGIFY2(amqp)     ,Amqp       );
    r.insert(QT_STRINGIFY2(http)     ,Http       );
    r.insert(QT_STRINGIFY2(https)    ,Https      );
    return r;
}

const QHash<QString, QStmRequestMethod> ___QStmRequestMethodType(){
    QHash<QString,QStmRequestMethod> r;
    r.insert(QT_STRINGIFY2(head),Head);
    r.insert(QT_STRINGIFY2(get),Get);
    r.insert(QT_STRINGIFY2(post),Post);
    r.insert(QT_STRINGIFY2(put),Put);
    r.insert(QT_STRINGIFY2(delete),Delete);
    r.insert(QT_STRINGIFY2(options),Options);
    r.insert(QT_STRINGIFY2(patch),Patch);
    r.insert(QT_STRINGIFY2(trace),Trace);

    r.insert(QT_STRINGIFY2(Head),Head);
    r.insert(QT_STRINGIFY2(Get),Get);
    r.insert(QT_STRINGIFY2(Post),Post);
    r.insert(QT_STRINGIFY2(Put),Put);
    r.insert(QT_STRINGIFY2(Delete),Delete);
    r.insert(QT_STRINGIFY2(Options),Options);
    r.insert(QT_STRINGIFY2(Patch),Patch);
    r.insert(QT_STRINGIFY2(Trace),Trace);
    return r;
}

const QHash<int, QString> ___QStmRequestMethodName(){
    QHash<int, QString> r;
    r.insert(Head,QT_STRINGIFY2(Head));
    r.insert(Get,QT_STRINGIFY2(Get));
    r.insert(Post,QT_STRINGIFY2(Post));
    r.insert(Put,QT_STRINGIFY2(Put));
    r.insert(Delete,QT_STRINGIFY2(Delete));
    r.insert(Options,QT_STRINGIFY2(Options));
    return r;
}

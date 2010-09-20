#include "yaz4py.h"
#include <string>
#include <string.h>
using namespace std;

//ZConnection::ZConnection(){
//    ZOOM_options o = ZOOM_options_create();
//    this->zc = ZOOM_connection_create(o);
//    ZOOM_options_destroy(o);
//}
/**
 *
 * @param zo
 */
ZConnection::ZConnection(const ZOptions* zo){
    this->zc = ZOOM_connection_create(zo->_getYazOptions());
}
ZConnection::~ZConnection() {
    ZOOM_connection_destroy(this->zc);
}
/**
 * @param hostname
 * @param portnum
 * @throw ZConnectionException
 */
void ZConnection::connect(const string &hostname, int portnum){

    ZOOM_connection_connect(this->zc, hostname.c_str(), portnum);
    int errcode;
    const char *errmsg;     // unused: carries same info as `errcode'
    const char *addinfo;
    if ((errcode = ZOOM_connection_error(this->zc, &errmsg, &addinfo)) != 0) {
    	string emessage(errmsg);
    	string eaddinfo(addinfo);
    	string message = emessage + " " + eaddinfo;
        throw ZConnectionException(message, errcode);
    }

}
/**
 * 
 * @param zq
 * @return
 */
ZResultSet* ZConnection::search(const ZQuery &zq){
    ZResultSet *rs = new ZResultSet(this, zq);
    return rs;
}

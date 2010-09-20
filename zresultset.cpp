#include "yaz4py.h"

#include <string>
using namespace std;
/**
 *
 * @param zc
 * @param zq
 * @throw ZConnectionException
 */
ZResultSet::ZResultSet(ZConnection *zc, const ZQuery &zq){
    ZOOM_connection yazc = zc->_getYazConnection();
    this->rs = ZOOM_connection_search(yazc, zq._getYazQuery());

    int errcode;
    const char *errmsg;     // unused: carries same info as `errcode'
    const char *addinfo;
    if ((errcode = ZOOM_connection_error(yazc, &errmsg, &addinfo)) != 0) {
    	string emessage(errmsg);
    	string eaddinfo(addinfo);
    	string message = emessage + " " + eaddinfo;
        //ZOOM_resultset_destroy(rs);
        throw ZConnectionException(message, errcode);
    }
}

ZResultSet::~ZResultSet(){
    ZOOM_resultset_destroy(rs);
}


void ZResultSet::setOption(const string &key, const string &value){
    ZOOM_resultset_option_set(this->rs, key.c_str(), value.c_str());
}
int ZResultSet::getSize() const{
    return ZOOM_resultset_size(this->rs);
}

ZRecord* ZResultSet::getRecord(int index){
    
    ZRecord *zr = new ZRecord(this, index);
    return zr;
}

void ZResultSet::setSetName(const string& param){
    this->setOption("setname", param);
}

void ZResultSet::setSchema(const string& param){
    this->setOption("schema", param);
}
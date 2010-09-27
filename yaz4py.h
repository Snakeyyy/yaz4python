/* 
 * File:   yaz4py.h
 * Author: sergey
 *
 * Created on 20 Июль 2010 г., 23:27
 */

#ifndef YAZ4PY_H
#define	YAZ4PY_H
#include <boost/python.hpp>
#include <yaz/zoom.h>
#include <string>
#include <boost/noncopyable.hpp>
#include <stdexcept>
using namespace std;
class ZQuery;
class ZResultSet;
class ZRecord;

class RunTimeError: public std::exception{
    string message;
    int code;
public:
    	RunTimeError(const string &message, const int code = 0){
		this->message = message;
		this->code = code;
	}
        ~RunTimeError()throw(){ }
        char const* what() const throw(){return this->message.c_str();}
        const string getMessage() const{
            return this->message;
	}
        void setMessage(string& message){
            this->message = message;
        }
        void setCode(const int code){
            this->code = code;
        }

};


class ZException:public std::exception{
	string message;
	int code;
public:
	ZException(const string &message, const int code = 0){
		this->message = message;
		this->code = code;
	}
        ~ZException()throw(){ }
        char const* what() const throw(){return this->message.c_str();}
	const int getCode() const{
		return this->code;
	}
	const string getMessage() const{
		return this->message;
	}
        void setMessage(string& message){
            this->message = message;
        }
        void setCode(const int code){
            this->code = code;
        }
};

class ZConnectionException:public ZException{
public:
    ZConnectionException(const string &message, const int code = 0):ZException(message, code){  }
};


class ZQueryException:public ZException{
public:
    ZQueryException(const string &message, const int code = 0):ZException(message, code){  }
};

class ZResultSetException:public ZException{
public:
    ZResultSetException(const string &message, const int code = 0):ZException(message, code){  }
};

class ZOptions{
    ZOOM_options zo;
    friend class ZConnection;
    ZOOM_options _getYazOptions() const {return zo;}
public:
    ZOptions();
    ~ZOptions();
    void del() {this->~ZOptions();}
    void setOption(const string &key, const string &value);
    void setImplementationName(const string&);
    void setUser(const string&);
    void setPassword(const string&);
    void setDatabase(const string&);
    void setCharset(const string&);
    void setGroup(const string&);
    void setSyntax(const string&);
    void setElementSetName(const string&);
};

class ZConnection{
    ZOOM_connection zc;
    friend class ZResultSet;
    ZOOM_connection _getYazConnection() const {return zc;}
public:
    //ZConnection();
    ZConnection(const ZOptions *zo = 0);
    ~ZConnection ();
    void connect (const string &hostname, int portnum);
    ZResultSet* search(const ZQuery &zq);
};

class ZQuery{
    ZOOM_query q;
    friend class ZResultSet;
    ZOOM_query _getYazQuery () const { return q; }
public:
    ZQuery(const string &query);
    ~ZQuery();
};

class ZResultSet{
    ZOOM_resultset rs;

    friend class ZConnection;
    friend class ZRecord; // for _getYazResultSet() & _getYazConnection()
    ZOOM_resultset _getYazResultSet () const { return rs; }
public:
    ZResultSet(ZConnection *zc, const ZQuery &zq);
    ~ZResultSet();
    void del() {this->~ZResultSet();}
    void setOption(const string &key, const string &value);
    int getSize() const;
    ZRecord* getRecord(int index);
    boost::python::list getRecords(size_t, size_t);
    void setSetName(const string&);
    void setSchema(const string&);
    void setSyntax(const string&);
};

class ZRecord{
    ZOOM_record zr;
    ZResultSet* zrs;
    friend class ZResultSet;
    ZOOM_record _getYazRecord () const { return zr; }
public:
    ZRecord();
    ZRecord(ZResultSet* zrs, int index);
    ~ZRecord();
    void del() {this->~ZRecord();}
    void setZoomRecord(ZOOM_record azr){zr = azr;}
    string render () const;
    string raw () const;
    string get(const string&);

};
#endif	/* YAZ4PY_H */


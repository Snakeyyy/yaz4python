# Python client for working with z39.50 protocol #
## 1. Example of usage. ##
```
import yaz4python
print dir(yaz4python)
try:
    zopt = yaz4python.ZOptions()
    zopt.set_database('voyager')
    zopt.set_syntax('usmarc')

    zconn = yaz4python.ZConnection(zopt)
    zconn.connect('z3950.loc.gov', 7090)

    zq = yaz4python.ZQuery('@attr 1=4 album')
    zrs = zconn.search(zq)

    print zrs.get_size()

    zrec = zrs.get_record(0)

    print zrec.raw()

    zrecs = zrs.get_records(5, 10)

    for rec in zrecs:
        print rec
except yaz4python.ZConnectionException as e:
    print e, e.code;
except yaz4python.ZQueryException as e:
    print e, e.code;
except yaz4python.ZResultSetException as e:
    print e, e.code;
#except Exception: is wrong !!!!!! it is not base for Z...Exceptions
```

## 2. Compilation. ##
Need the following libraries:
**[boost\_python](http://www.boost.org/doc/libs/1_44_0/libs/python/doc/index.html),**[yaz](http://www.indexdata.com/yaz)
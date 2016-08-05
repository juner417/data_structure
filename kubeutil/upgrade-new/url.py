#!/usr/bin/python 
import urllib2, os, sys
import simplejson
def get_api( url):
    # get api result
    try:
        # using json
        res = simplejson.load(urllib2.urlopen(url))
    except urllib2.HTTPError as err:
        logging.error(err - url)
        sys.exit(2)
    except urllib2.URLError as err:
        logging.error(err - url)
        sys.exit(2)
    return res

if __name__=='__main__':

    url = 'http://hdtest-4x8-0001:8080/api/v1/nodes/'
    res = get_api(url)
    #print(res)
    print(res['status']['nodeInfo'])

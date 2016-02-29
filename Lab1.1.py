# -*-coding: utf-8 -*-
import urllib2
from datetime import datetime

# downloading and renaming files
for x in xrange(1,26):
    url = "http://www.star.nesdis.noaa.gov/smcd/emb/vci/gvix/G04/ts_L1/ByProvince/Mean/L1_Mean_UKR.R%02i.txt" % x
    #print str(x) + "." + url
    vhi_url = urllib2.urlopen(url)
    filename =  'VHI/vhi_id_%02i_%s.csv' % (x, datetime.now().strftime('%Y-%m-%d_%H:%M:%S'))
    #print filename
    out = open(filename,'wb')
    out.write(vhi_url.read())
    out.close()
    #print newfilename
print "All VHI are downloaded..."

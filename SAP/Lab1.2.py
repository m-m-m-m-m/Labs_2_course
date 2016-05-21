# -*-coding: utf-8 -*-
import pandas as pd
from glob import glob
import os, re
import urllib2
from datetime import datetime

# downloading and renaming files
def download_files():
    for x in xrange(1,26):
        url = "http://www.star.nesdis.noaa.gov/smcd/emb/vci/gvix/G04/ts_L1/ByProvince/Mean/L1_Mean_UKR.R%02i.txt" % x
        #print str(x) + "." + url
        vhi_url = urllib2.urlopen(url)
        filename =  'VHI/vhi_id_%02i_%s.csv' % (x, datetime.now().strftime('%Y-%m-%d_%H:%M:%S'))
        #print filename
        out = open(filename,'wb')
        out.write(vhi_url.read())
        out.close()
    print "Усі файли завантажено."

indices = {     1:  'Вінницька',
                2:  'Волинська',
                3:  'Дніпропетровська',
                4:  'Донецька',
                5:  'Житомирська',
                6:  'Закарпатська',
                7:  'Запорізька',
                8:  'Івано-Франківська',
                9:  'Київська',
                10:  'Кіровоградська',
                11:  'Луганська',
                12:  'Львівська',
                13:  'Миколаївська',
                14:  'Одеська',
                15:  'Полтавська',
                16:  'Рівенська',
                17:  'Сумська',
                18:  'Тернопільська',
                19:  'Харківська',
                20:  'Херсонська',
                21:  'Хмельницька',
                22:  'Черкаська',
                23:  'Чернівецька',
                24:  'Чернігівська',
                25:  'Республіка Крим'
            }

def read_information(filepath):
    return pd.read_csv(filepath,index_col=False, header=1)

def change_indices():
    for filename in sorted(glob('VHI/vhi_id_[0-9]*')):
        new_filename = '%s%s%s' % (filename[:11], indices[int(filename[11:13])],filename[13:])
        print '%s renamed to %s' % (filename, new_filename)
        os.rename(filename, new_filename)

def VHI_min_max(index, year):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[0])
    #print df
    df = df.loc[df['year'] == year]['VHI']
    print 'VHI за %s рік (%s область):' % (str(year), indices[index])
    for number, week in enumerate(df):
        print '%s. %s' % (str(number+1), str(week))
    print 'Max VHI = %s' % str(df.max())
    print 'Min VHI = %s' % str(df.min())

def VHI_extreme(index, percent):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[0])
    df = df.loc[df['%Area_VHI_LESS_15'] > percent]['year']
    #print df
    df = set(df)
    years = list(df)[1:]
    print 'Роки з екстримальними посухами, які торкнулися більше %s відсотків площі (%s область):' % (str(percent), indices[index])
    for index, year in enumerate(years):
        print '%s. %s' % (str(index+1), str(year))

'''def VHI_temperate(index, percent):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[0])
    df = df.loc[df['%Area_VHI_LESS_35'] > percent]['year']
    #print df
    df = set(df)
    years = list(df)[1:]
    print 'Роки з помірними посухами, які торкнулися більше %s відсотків площі (%s область):' % (str(percent), indices[index])
    for index, year in enumerate(years):
        print '%s. %s' % (str(index+1), str(year))'''


#download_files()
#path = raw_input("Enter filepath:")
path = sorted(glob('VHI/vhi_id_[0-9]*'))
#information = read_information(path[0])
#print information
change_indices()
VHI_min_max(1, 2000)
VHI_extreme(1, 10)
#VHI_temperate(2, 30)

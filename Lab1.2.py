# -*-coding: utf-8 -*-
import pandas as pd
from glob import glob
import os, re

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
                25:  'Республіка Крим',
                '01':  'Вінницька',
                '02':  'Волинська',
                '03':  'Дніпропетровська',
                '04':  'Донецька',
                '05':  'Житомирська',
                '06':  'Закарпатська',
                '07':  'Запорізька',
                '08':  'Івано-Франківська',
                '09':  'Київська',
                '10':  'Кіровоградська',
                '11':  'Луганська',
                '12':  'Львівська',
                '13':  'Миколаївська',
                '14':  'Одеська',
                '15':  'Полтавська',
                '16':  'Рівенська',
                '17':  'Сумська',
                '18':  'Тернопільська',
                '19':  'Харківська',
                '20':  'Херсонська',
                '21':  'Хмельницька',
                '22':  'Черкаська',
                '23':  'Чернівецька',
                '24':  'Чернігівська',
                '25':  'Республіка Крим'
            }

def read_information(filepath):
    return pd.read_csv(filepath,index_col=False, header=1)

def change_indices():
    for filename in sorted(glob('VHI/vhi_id_\d{2}')):
        #print filename
        newfilename = filename[:11] + indices[filename[11:13]] + filename[13:]
        #print new_filename
        os.rename(filename, new_filename)

def VHI_min_max(index, year):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[-1])
    df = df.loc[df['year'] == year]['VHI']
    print 'Max VHI = ' + str(df.max())
    print 'Min VHI = ' + str(df.min())
    #print ' '.join([str(df.max()), str(df.min())])
    #return df

def VHI_extreme(index, percent):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[-1])
    df = df.loc[df['%Area_VHI_LESS_15'] > percent]['year']
    #print df
    df = set(df)
    df = list(df)[1:]
    print df

def VHI_temperate(index, percent):
    regex = 'VHI/vhi_id_%s*' % indices[index]
    df = read_information(glob(regex)[-1])
    df = df.loc[df['%Area_VHI_LESS_35'] > percent]['year']
    #print df
    df = set(df)
    df = list(df)[1:]
    print df

#path = raw_input("Enter filepath:")
path = 'VHI/vhi_id_Вінницька_2016-02-26_01:54:23.csv'
information = read_information(path)
#print information
change_indices()
#VHI_min_max(1, 2000)
VHI_extreme(1, 10)
VHI_temperate(2, 30)

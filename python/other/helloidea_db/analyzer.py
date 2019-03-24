import sqlite3
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from collections import OrderedDict


database_filename = 'production.sqlite3'
with sqlite3.connect(database_filename) as conn:
    tables = ['users', 'topics', 'ideas', 'words']

    for target in tables:
        df = pd.read_sql_query('SELECT * FROM {}'.format(target), conn)
        
        datestr_item_table = OrderedDict()
        item_count = 0
        for time in df['created_at']:
            date  = time.split(' ')[0]
            item_count += 1
            datestr_item_table[date] = item_count

        x = np.array(list(datestr_item_table.keys()))
        y = np.array(list(datestr_item_table.values()))

        plt.figure(figsize=(4.0, 3.0), dpi=1500)
        plt.title(target)
        plt.xticks([])
        plt.plot(x, y, linewidth=3.0, label=target)
        plt.savefig('{}.png'.format(target))

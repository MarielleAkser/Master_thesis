import os
import glob

import numpy as np
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go

# Opens the corresponding files, Run5 has 10 000 events
xe133_files = glob.glob("xe133_tripleRun4_*.csv")
xe135_files = glob.glob("../Xe135/xe135_tripleRun1_*.csv")

li_133 = []
for filename in xe133_files:
    _df_133 = pd.read_csv(filename, comment="#", header = None)
    li_133.append(_df_133)

_data_133 = pd.concat(li_133, axis=0)
data_133 = _data_133[[7]]
data_133.columns = ["CE_133"]

li_135 = []
for filename in xe135_files:
    _df_135 = pd.read_csv(filename, comment="#", header = None)
    li_135.append(_df_135)

_data_135 = pd.concat(li_135, axis=0)
data_135 = _data_135[[7]]
data_135.columns = ["CE_135"]

# Only get values in coincidence & when gamma = 31.6 keV and CE is between 0.04 and 0.5
data_133 = data_133[ (data_133["CE_133"] > 0)]
data_135 = data_135[ (data_135["CE_135"] > 0)]

fig = go.Figure()
fig.add_trace(go.Histogram(
    x = data_133["CE_133"],
    # xaxis2 = 'x2',
    yaxis = 'y2',
        marker = dict(
                color = 'rgba(63,121,181,1)')
))
fig.add_trace(go.Histogram(
    x = data_135["CE_135"],
    # xaxis = 'x1',
    yaxis = 'y1',
        marker = dict(
                color = 'rgba(63,121,181,1)')
))
fig.update_layout(
    autosize = False,
    xaxis = dict(
        zeroline = False,
        domain = [0,1],
        showgrid = False
    ),
    yaxis = dict(
        zeroline = False,
        domain = [0,0.45],
        showgrid = False
    ),
    yaxis2 = dict(
        zeroline = False,
        domain = [0.50,0.95],
        showgrid = False
    ),
    height = 600,
    width = 1000,
    bargap = 0,
    hovermode = 'closest',
    showlegend = False,
    xaxis_title="[MeV]",
    yaxis_title="Counts",
    yaxis2_title="Counts",
    title={
        'text': "Histogram over the energy deposit for the conversion electrons",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'}
)
fig.show()
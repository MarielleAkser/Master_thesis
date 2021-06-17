import os
import glob

import numpy as np
import pandas as pd
import plotly.express as px
import plotly.graph_objects as go

# Opens the corresponding files, Run5 has 10 000 events
all_files = glob.glob("xe135_tripleRun1_*.csv")

li = []
for filename in all_files:
    _df = pd.read_csv(filename, comment="#", header = None)
    li.append(_df)

_data = pd.concat(li, axis=0)
data = _data[[1, 7, 11]]
data.columns = ["gamma", "CE", "beta"]

# Only get values in coincidence & when gamma = 31.6 keV
data = data[(data["gamma"] == 0.0316)]
data = data[(data["CE"] > 0)]
data = data[(data["beta"] > 0)]

fig = go.Figure()
fig.add_trace(go.Histogram2dContour(
    x = data["CE"],
    y = data["beta"],
    colorscale = 'Blues'))
fig.add_trace(go.Histogram(
        y = data["beta"],
        xaxis = 'x2',
        marker = dict(
            color = 'rgba(63,121,181,1)'
        )
    ))
fig.add_trace(go.Histogram(
        x = data["CE"],
        yaxis = 'y2',
        marker = dict(
                color = 'rgba(63,121,181,1)'
        )
    ))
fig.update_layout(
    autosize = False,
    xaxis = dict(
        zeroline = False,
        domain = [0,0.8],
        showgrid = False
    ),
    yaxis = dict(
        zeroline = False,
        domain = [0,0.8],
        showgrid = False
    ),
    xaxis2 = dict(
        zeroline = False,
        domain = [0.83,1],
        showgrid = False
    ),
    yaxis2 = dict(
        zeroline = False,
        domain = [0.85,1],
        showgrid = False
    ),
    height = 600,
    width = 1000,
    bargap = 0,
    hovermode = 'closest',
    showlegend = False,
    xaxis_title="CE [MeV]",
    xaxis_range=(0.2,0.214),
    yaxis_title="Beta [MeV]",
    yaxis2_title="Counts",
    xaxis2_title="Counts",
    title={
        'text': "Histogram over the energy deposit for the beta- and CE-particle for Xe-135",
        'y':0.9,
        'x':0.5,
        'xanchor': 'center',
        'yanchor': 'top'}
#     legend_title="Particle count",

)
fig.show()
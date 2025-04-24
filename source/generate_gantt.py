import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

df = pd.read_csv("../GANTT.csv", sep=';', decimal=',')

fig, ax = plt.subplots(figsize=(10, 6))

for i, row in df.iterrows():
    label = f"{int(row['Od'])} ➝ {int(row['Do'])}"
    start = row['Start']
    duration = row['Czas']
    color = 'red' if row['Krytyczny'] == 'TAK' else 'skyblue'
    ax.barh(label, duration, left=start, color=color)

# Opisy osi i tytuł
ax.set_xlabel("Czas")
ax.set_title("Wykres Gantta – Aktywności PERT")
ax.grid(True)

#Dodanie legendy
critical_patch = mpatches.Patch(color='red', label='Krytyczna aktywność')
non_critical_patch = mpatches.Patch(color='skyblue', label='Zapas czasu (niekrytyczna)')
ax.legend(handles=[critical_patch, non_critical_patch])

# Zapis
plt.tight_layout()
plt.savefig("../GANTT.png")

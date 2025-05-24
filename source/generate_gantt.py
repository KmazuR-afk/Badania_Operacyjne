import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# Wczytanie danych z pliku CSV
df = pd.read_csv("../GANTT.csv", sep=';', decimal=',')

fig, ax = plt.subplots(figsize=(10, 6))

for i, row in df.iterrows():
    label = f"{int(row['Od'])} ➝ {int(row['Do'])}"
    start = row['Start']
    duration = row['Czas']
    slack = row['Slack']
    color = 'red' if row['Krytyczny'] == 'TAK' else 'skyblue'

    # Rysuj cień zapasu (Slack) – szary prostokąt
    if slack > 0:
        ax.barh(label, slack, left=start, color='lightgray', alpha=0.5, edgecolor='none')

    # Rysuj główny pasek zadania
    ax.barh(label, duration, left=start, color=color)

# Opisy osi i tytuł
ax.set_xlabel("Czas")
ax.set_title("Wykres Gantta – Aktywności PERT z zapasem czasu (Slack)")
ax.grid(True)

# Legenda
critical_patch = mpatches.Patch(color='red', label='Krytyczna aktywność')
non_critical_patch = mpatches.Patch(color='skyblue', label='Niekrytyczna aktywność')
slack_patch = mpatches.Patch(color='lightgray', alpha=0.5, label='Zapas czasu (Slack)')
ax.legend(handles=[critical_patch, non_critical_patch, slack_patch])

# Zapis do pliku
plt.tight_layout()
plt.savefig("../GANTT.png")

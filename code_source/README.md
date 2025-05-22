# Anneau - Projet Réseau

## ▶️ Lancement manuel

### Étapes à suivre (ordre **obligatoire**) :
1. Ouvrir **3 terminaux différents**.
2. Dans le **premier terminal**, exécuter :
   ```bash
   ./pc3.run
   ```
3. Dans le deuxième terminal, exécuter :
   ```bash
   ./pc2.run
   ```
4. Dans le troisième terminal, exécuter :
   ```bash
   ./pc3.run
   ```

⚠️ Il est impératif de respecter cet ordre.

## 🚀 Lancement automatique (si konsole est disponible)

Un script start.sh est fourni pour lancer automatiquement les 3 hôtes dans des onglets séparés de konsole.

### Lancer le script :

```bash
bash start.sh
```

Ce script effectue :
- La compilation des programmes
- Le lancement de pc1.run, pc2.run et pc3.run dans des onglets distincts via konsole (terminal de kde)

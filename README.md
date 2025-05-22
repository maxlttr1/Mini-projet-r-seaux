# Anneau - Projet Réseau

Ce projet implémente un protocole de **communication en anneau (token ring)** entre plusieurs hôtes, utilisant le protocole **UDP** sous Linux. Chaque nœud communique avec le suivant dans un cycle circulaire.

---

## ⚙️ Fonctionnement

Le système repose sur une circulation d’un **jeton (token)** entre 3 ordinateurs (ou processus). Lorsqu’un hôte reçoit ce jeton, il peut choisir d’envoyer un message à un autre hôte. Ce message circule ensuite jusqu’à son destinataire, qui le lit, puis libère le jeton à nouveau (il peut alors lui aussi choisir d'envoyer un message ou non).

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

## Structure du projet
```bash
.
├── src/
│   ├── main_pc1.c
│   ├── main_pc2.c
│   ├── main_pc3.c
│   ├── utils.c
│   └── ...
├── include/
│   ├── constants.h
│   ├── FDU.h
│   └── utils.h
├── Makefile
├── start.sh
└── README.md
```
# 🛋️ Hïkěà - Gestionnaire de Catalogue

## 📋 À propos
Hïkěà est une application de gestion de catalogue de meubles et d'articles de décoration développée avec Qt. Elle permet de consulter, ajouter, modifier et gérer un inventaire complet de produits avec leurs caractéristiques détaillées.

## 🎯 Fonctionnalités
- 📝 Consultation des articles par catégorie
- ➕ Ajout de nouveaux articles
- 🔄 Modification des articles existants
- 🔍 Recherche d'articles
- 🌈 Gestion des différentes finitions et couleurs
- 🌐 Support multilingue (Français/Anglais)
- 💾 Sauvegarde au format JSON

## 🏗️ Structure du Projet
- 📁 `img/` : Contient les images nécessaires à l'affichage
- 📁 `data/` : Stockage des fichiers JSON
  - data.json (fusion des deux jeux de données)
- 📁 `src/` : Code source de l'application
  - Fichiers principaux (.cpp, .h)
  - Interfaces utilisateur (.ui)

## 👥 Équipe
- Robin HILAIRE
- Simon MILLET

## 🛠️ Technologies Utilisées
- Qt 6.5.0
- C++
- JSON pour le stockage des données

## 📱 Interface Utilisateur
L'application propose une interface intuitive avec :
- Liste des articles avec filtrage par catégorie
- Panneau de détails pour chaque article
- Gestion des finitions et disponibilités
- Barre de recherche
- Menu d'options et de paramètres

## 📦 Catégories de Produits
- 🪑 Meubles
- 🎨 Décoration
- 📦 Rangement
- 🛏️ Literie
- 🍳 Cuisine
- 💡 Éclairage

## 💫 Caractéristiques des Articles
Chaque article comprend :
- Nom et numéro de référence
- Description détaillée
- Dimensions (longueur, largeur, profondeur)
- Poids
- Designer
- Photo
- Finitions disponibles
- Prix
- Stock disponible

## 🔧 Installation
1. Cloner le dépôt
2. Ouvrir le projet dans Qt Creator
3. Compiler et exécuter l'application

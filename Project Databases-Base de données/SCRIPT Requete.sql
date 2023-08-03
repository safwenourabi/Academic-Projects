--affichage des donn�es du tableau entreprise
SELECT entreprise.nom
FROM entreprise ;




-- 	Le nom du tuteur du projet pacte Helma. 
SELECT enseignant.nomfr ,enseignant.prenomfr 
FROM enseignant , projet
WHERE (projet.id_enseignant= enseignant.id_enseignant) and 
      (UPPER(projet.nom)='HELMA');



--	Le d�partement de l�enseignant qui encadre le projet pacte intitul� wajahni.
SELECT departement.abreviation
FROM enseignant, projet,departement
WHERE projet.id_enseignant = enseignant.id_enseignant
and enseignant.id_dep= departement.id_dep 
and 
      (UPPER(projet.nom)='HELMA');
      
      
      
--Le nom de l�entreprise qui est en collaboration avec l��quipe du projet d'identifiant 8.
SELECT entreprise.nom
FROM entreprise,est_en_collaboration_avec
WHERE entreprise.id_entreprise= est_en_collaboration_avec.id_entreprise and est_en_collaboration_avec.id_projet=8;



--faire le mise a jour de telephone de l'etdudiant ayant le "nom" ourabi et le prenom "safwen"
UPDATE etudiant
SET etudiant.numtel = 92739560
WHERE UPPER(etudiant.nomfr)='OURABI' and  UPPER(etudiant.prenomfr)='SAFWEN';



--Afficher les �quipes qui comporte plus que deux etudiant 
SELECT id_equipe
FROM "EST_FORM�E_PAR"
GROUP BY EST_FORM�E_PAR.id_equipe
HAVING count(*) >2 ;



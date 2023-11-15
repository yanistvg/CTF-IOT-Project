#include "headers/interactWithReader.h"

/*
find_card_reader : permet de rechercher des lecteur de carte en completant une structure
card_reader_t qui contient les informations pour pouvoir lister et se connecter a une carte

input :
    card_reader_t ** : structure qui serat remplit des informations si pas d'erreur
                       sinon serat initialise a NULL

output:
	_SUCCESS_ : si pas d'erreur
	_NOT_NULL_ : si cardReader est deja initialise (si pas NULL)
	_MOLLOC_ERROR_ : en ca d'erreur d'allocation de memoire
	SCARD_E_INVALID_PARAMETER : si le Ph context est NULL
	SCARD_E_INVALID_VALUE : si le type de scope est invalide
	SCARD_E_NO_MEMORY : probleme d'allocation
	SCARD_E_NO_SERVICE : le serveur n'est pas alume
	SCARD_F_COMM_ERROR : erreur de communication interne
	SCARD_F_INTERNAL_ERROR : erreru interne
*/
int find_card_reader(card_reader_t **cardReader) {
	LONG rv;

	if (*cardReader != NULL) return _NOT_NULL_;

	*cardReader = malloc(sizeof(card_reader_t));
	if (*cardReader == NULL) return _MOLLOC_ERROR_;

	rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &( (*cardReader)->hContext ));
	if (rv != SCARD_S_SUCCESS) {
		free(*cardReader);
		*cardReader = NULL;
		return rv;
	}

	#ifdef SCARD_AUTOALLOCATE
		(*cardReader)->dwReaders = SCARD_AUTOALLOCATE;

		rv = SCardListReaders(
			(*cardReader)->hContext,
			NULL,
			(LPTSTR)&(*cardReader)->mszReaders,
			&(*cardReader)->dwReaders
		);
		if (rv != SCARD_S_SUCCESS) {
			free(*cardReader);
			*cardReader = NULL;
			return rv;
		}
	#else
		rv = SCardListReaders((*cardReader)->hContext, NULL, NULL, &(*cardReader)->dwReaders);
		if (rv != SCARD_S_SUCCESS) { free(*cardReader); *cardReader = NULL; return rv; }

		(*cardReader)->mszReaders = calloc((*cardReader)->dwReaders, sizeof(char));
		
		rv = SCardListReaders(
			(*cardReader)->hContext,
			NULL,
			(*cardReader)->mszReaders,
			&(*cardReader)->dwReaders
		);
		if (rv != SCARD_S_SUCCESS) { free(*cardReader); *cardReader = NULL; return rv; }
	#endif

	return _SUCCESS_;
}
#include "../phylosopher.h"

t_phlst	*init_phylo_list(t_phlst *plist, int n)
{
	int	i;

	i = 1;
	plist = malloc(sizeof(t_phlst));
	plist->index = 1;
	i++;
	while(i <= n)
	{
		plist = malloc(sizeof(t_phlst));
		plist->index = i;

	}
}

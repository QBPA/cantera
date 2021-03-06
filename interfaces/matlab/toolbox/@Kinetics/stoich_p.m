function nu_p = stoich_p(a, species, rxns)
% STOICH_P  Get the product stoichiometric coefficients.
% nu_p = stoich_p(a,species,rxns)
%
% See also: :mat:func:`stoich_r`, :mat:func:`stoich_net`
%
% :param a:
%     Instance of class :mat:func:`Kinetics` (or another
%     object deriving from Kinetics)
%     for which the product stoichiometric coefficients are desired.
% :param species:
%     Species indices for which product stoichiometric coefficients
%     should be retrieved. Optional argument; if specified, ``rxns``
%     must be specified as well.
% :param rxns:
%     Reaction indices for which product stoichiometric coefficients
%     should be retrieved. Optional argument; if specified, ``species``
%     must be specified as well.
% :return:
%     Returns a sparse matrix of all product stoichiometric
%     coefficients. The matrix element ``nu(k,i)`` is the
%     stoichiometric coefficient of species k as a product in
%     reaction i. If ``species`` and ``rxns`` are specified, the matrix
%     will contain only entries for the specified species and
%     reactions. For example, ``stoich_p(a,3,[1 3 5 7])`` returns a
%     sparse matrix containing only the coefficients for species 3
%     in reactions 1, 3, 5, and 7.
%

nsp = nTotalSpecies(a);
nr = nReactions(a);
b = sparse(nsp, nr);
if nargin == 1
    kvals = 1:nsp;
    ivals = 1:nr;
elseif nargin == 3
    kvals = species;
    ivals = rxns;
else
    error('stoich_p requires 1 or 3 arguments.')
end

for k = kvals
    for i = ivals
        nu = kinetics_get(a.id, 6, i, k);
        if nu ~= 0.0
            b(k, i) = nu;
        end
    end
end
nu_p = b;

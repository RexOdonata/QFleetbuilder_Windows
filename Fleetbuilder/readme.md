**QFleet Fleetbuilder**

Fleetbuilder allows users to create lists for Dropfleet commander. It features saving and loading compressed lists (.dfc) files as well as writing html lists, strategy  deck cards and profile cards.

It requires two subdirectories colocated with the binary/executable for proper functions:
* data: holds 'ships.qfs'
* htmlTemplates: holds the NL::Template .txt files

Not being able to access files in either of these subdirectories will cause application errors.

Fleetbuilder uses:  
* NL::Template by catnap games.
* LZ4 by Yann Collet


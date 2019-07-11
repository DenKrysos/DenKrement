# DenKrement


To compile the project "exactly as is", some *Trick specific to Eclipse* is required as described in <main.c>

It makes heavy use of "DenKr_essentials" to implement a running Framework for "Modular Interaction".
The basic idea behind it is, that "real operational Functionality" is implemented as plugins/modules, using "DenKrement_plugins".
These plugins may interact using the DenKrement / DenKr_essentials possiblities.
Also Python Scripts can communicate with a running DenKrement, if the plugin "DenKrement_plugin_predefined__connect_external_Python" is present and the Python Script is using "DenKrement_extern_Python"

.. _diferences:

#################################
  Fork Differences
#################################

Copyright (c) 2024 Gothic 2 Online Team

Gothic 2 Online modification uses modified Squirrel version with some new features
and changes added to it. The original language did lack some functionallity, hence
why it was extended to better fit modern standards. Some changes might affect
the compatibility with original language.

==================
New features
==================

- **local class** expression is now supported
- **_get** metamethod will also affect **in** operator
- Class instances now support **foreach** iteration

==================
New functionality
==================

- **geterrorhandler** function
- **getdefaultdelegate** function
- **setreleasehook** function
- **getstacktop** function (used for debugging only)
- **getstacksize** function (used for debugging only)
- **rawstring** function
- **dump** function
- **min** function
- **max** function
- **clamp** function
- **lerp** function
- **round** function
- **random** function
- **randomseed** function
- **file.read** method
- **file.write** method
- **blob.read** method
- **blob.write** method
- **blob.tostring** method
- **thread.acall** method
- **regexp.captureall** method

==================
Changes
==================

- **regexp** modern engine support via C++ STL regex library used under the hood
- **regexp** capture methods support optional groups by returning **null** in array results
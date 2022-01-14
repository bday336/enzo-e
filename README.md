This branch of Enzo-E is my functioning version that is up to date with the main branch of the original Enzo-E repository. I am developing this script to produce the bondi accretion initial problem. My plan right now is to use the IsolatedGalaxy problem as a starting point rather than the depreciated Collapse problem as a starting point. It seems that the current main branch does not even run the Collapse test problem anymore, I think.

That being said, I will use this readme file as a written log of my progress so that I do not get confused with the various versions of Enzo-E I have built on PACE.

Jan 13, 2022: I was able to get git integrated on PACE and use it to clone the current main branch of Enzo-E as well as make various branches on my own fork. I have the main branch setup as the unbuilt version of the up to date original repository branch. The built branch does not seem to be important at this point given that I have the uptodate branch. I might delete it at some point. The uptodate branch is able to run the IsolatedGalaxy problem so that I what I plan to use as the base template for the Bondi accretion problem. This should be better than the Collapse problem because 1) it runs on the branch and 2) it already has the integration of particles and gas built into the problem.

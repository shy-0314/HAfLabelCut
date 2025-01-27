# HAfLabelCut
Provide source code and experimental data for paper A Simple Heuristic Finding Connectivity Bottleneck in Networks with Shared Risk Resource Groups.

## ABSTRACT
A shared risk resource group means a set of resources that share the same risk. Computer network with shared risk resource groups can be modeled as a labeled graph. The fundamental connectivity concept in labeled graphs can be in turn modeled as the Label s-t Cut problem. Given a graph with labels defined on edges, a source s and a sink t, the problem is to find minimum number of labels such that the removal of edges having these labels can disconnect s and t. 

The Label s-t Cut problem is NP-hard and has several approximation algorithms.
However, there lack heuristic algorithms with better practical performance. We propose a Monte Carlo heuristic algorithm for the problem. The main contribution is a concept of the minimal subgraph connecting s and t, which is inspired by Menger's Theorem.
Based on this concept, we devise a Monte Carlo strategy to score labels in order to find the labels that appear most frequently in any feasible solutions. Our heuristic then picks the top labels with the highest scores to form a feasible solution. 
Experimental simulations on random instances show that the heuristic overwhelmingly outperforms the best approximation algorithm for the problem.

## Experimental Results
<div align="center">
<img src="/pic/config.png"  title="Results on dataset config" alt="Results on dataset Config" width="600">
</div>
<div align="center">
    <img src="/pic/gnp0.2.png" title="Results on dataset GNP p=0.2" alt="Results on dataset GNP p=0.2" width="300">
    <img src="/pic/gnp0.5.png" title="Results on dataset GNP p=0.5" alt="Results on dataset GNP p=0.5" width="300">
    <img src="/pic/gnp0.8.png" title="Results on dataset GNP p=0.8"alt="Results on dataset GNP p=0.8" width="300">
</div>
<div align="center">
<img src="/pic/spg.png"  title="Results on dataset SPG" alt="Results on dataset SPG" width="600">
</div>

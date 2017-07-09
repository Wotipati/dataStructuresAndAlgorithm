# kirchhoff.py

##### 行列木定理が成り立っているか確認するコード  

    $ python kirchhoff.py --dim_fn <total node>

`--dim_fn <total node>`の部分でノードの数を指定する  
指定しなければ5つのノードの場合で計算する  

実行例  

    $ python kirchhoff.py --dim_fn 5  


結果

    Adjacency matrix  
    [[ 0.  1.  1.  0.  0.]  
     [ 1.  0.  0.  1.  0.]  
     [ 1.  0.  0.  1.  1.]  
     [ 0.  1.  1.  0.  0.]  
     [ 0.  0.  1.  0.  0.]]  
    Laplacian matrix  
    [[ 2. -1. -1.  0.  0.]  
     [-1.  2.  0. -1.  0.]  
     [-1.  0.  3. -1. -1.]  
     [ 0. -1. -1.  2.  0.]  
     [ 0.  0. -1.  0.  1.]]  
    cofactors  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
    4.0  
  

出力グラフ  
<img width="443" alt="graph" src="https://user-images.githubusercontent.com/26996041/27993564-f082bae2-64e7-11e7-93be-b21497897f00.png">
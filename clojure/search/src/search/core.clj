(ns search.core)

;; returns the index of key if it exists in coll, otherwise returns nil
(defn binary-search [coll key]
  (let [coll (vec coll)]
    (loop [imin 0
           imax (- (count coll) 1)]
      (if (< imax imin) nil
          (let [imid (int (+ imin (/ (- imax imin) 2)))]
            (do (println imin imax imid)
                (cond (> (coll imid) key)
                      (recur imin (- imid 1))
                      (< (coll imid) key)
                      (recur (+ imid 1) imax)
                      :else imid)))))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Binary Tree Problem Spec
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defrecord Node [state parent action pc])

(defn prn-node [node] (prn (:state node)))

;; Successor function (Transition Model)
(defn succ [node actions]
  (if (< (:pc node) 5)
    (for [a actions]
      (Node. (+ (:state node) (rand-int 6))
             node
             a
             (+ 1 (:pc node))))
    []))

(def bin-tree-problem {:init-state (Node. 0 nil nil 0)
              :actions [:left :right]
              :succ-fn succ
              :goal-test (fn [n] (> (:state n) 37))})


;; depth-first search: returns path or nil if no goal is found
(defn dfs [problem]
  (loop [node (:init-state problem)
         frontier #{}
         explored []]
    (let [f (into frontier (reverse (succ node (:actions problem))))]
      (cond ((:goal-test problem) node) explored 
            (empty? f) (prn (str "failed after searching " (count explored) " nodes")) 
            :else
            (recur (first f) (rest f)
                   (conj explored (:state (:parent node))))))))






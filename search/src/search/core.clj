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


;; TODO: needs parent attribute
(defrecord Node [state left right action path-cost])

(def a (Node. 'a
              (Node. 'b 
                     (Node. 'd nil nil :left 2)
                     (Node. 'e nil nil :right 2)
                     :left 1)
              (Node. 'c 
                     (Node. 'f nil nil :left 2)
                     (Node. 'g nil nil :right 2)
                     :right 1)
              nil 0))

;; TODO: needs the rest of problem spec
(def problem {:root a
              :actions [:left :right]})

;; true if node satisfies goal-state in prob, false otherwise
(defn goal-test [goal node]
  (= (:state node) goal))

;; evaluates to child nodes of node
(defn children-of [node problem]
  (remove nil? (for [ac (:actions problem)]
                 (ac node))))

;; depth-first search: evaluates to the search path or nil if not found
(defn dfs [problem goal]
  (loop [node (:root problem)
         frontier #{}
         path [(:state node)]]
    (let [f (into frontier (reverse (children-of node problem)))]
      (cond (goal-test goal node) path                                             ;; success
            (empty? f) (prn (str "failed after searching " (count path) " nodes")) ;; failure
            :else
            (recur (first f)
                   (rest f)
                   (conj path (:state (first f))))))))





(ns online-dfs-agent.core
  (:use [search.core]))


(def ^:const locsize 3)
(def ^:const wallsize 7)
(def ^:const length (* locsize locsize))
(def untried ())

(defn goal-test [loc]
  (and (= (:x loc) 2)
       (= (:y loc) 2)))

(def online-dfs-agent [loc env]
  (cond (goal-test loc)
        (do (prn "AT GOAL STATE")
            't)

        (not (nil? (binary-search untried loc) )
             
             ))



  )

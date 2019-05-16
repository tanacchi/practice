; REMove a memBER or REmove a meMBER

(define rember
  (lambda (elem lat)
    (cond
      ((null? lat) '())
      ((eq? elem (car lat)) (cdr lat))
      (else (cons (car lat) (rember elem (cdr lat)))))))

(print (rember 2 '(0 1 2 3 4 5 6)))
(print (rember 7 '(0 1 2 3 4 5 6)))

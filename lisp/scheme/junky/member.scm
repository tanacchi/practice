(define member?
  (lambda (elem lat)
    (cond
      ((null? lat) #f)
      ((eq? elem (car lat)) #t)
      (else (member? elem (cdr lat))))))

(print (member? 2 '(0 1 2 3 4 5)))
(print (member? 6 '(0 1 2 3 4 5)))

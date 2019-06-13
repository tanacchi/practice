(define (totient-phi target)
  (define (totient-phi-aux target count result)
    (cond
      ((eq? target count) result)
      ((comprime target count) 
       (display count)
       (newline)
       (totient-phi-aux target (+ count 1) (+ result 1)))
      (else (totient-phi-aux target (+ count 1) result))))
  (cond
    ((eq? target 1) 1)
    (else (totient-phi-aux target 1 0))))

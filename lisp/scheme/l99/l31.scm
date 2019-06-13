(define (is-prime num)
  (define (is-prime-aux target count)
    (cond
      ((eq? target count) #t)
      ((zero? (modulo target count)) #f)
      (else (is-prime-aux target (+ count 1)))))
  (is-prime-aux num 2))

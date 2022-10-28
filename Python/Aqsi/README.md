run script:
python main.py -a (transaction ammount)


example:
python main.py -a 150


good json example:
16.09.2022 14:42::26.638
{
    "acquiringData": {
        "AID": "A0000006581010",
        "APN": "MIR PAY",
        "IIN": "MIR PAY",
        "RRN": "225911261521",
        "TSI": "",
        "TVR": null,
        "acquirerAgentName": "2can",
        "acquirerBankName": "ВТБ",
        "amount": 1,
        "approvalCode": "303535313931",
        "cardholder": null,
        "cashlessType": 2,
        "date": "2022-09-16T14:42:22.000+03:00",
        "errorCode": "00",
        "errorMessage": null,
        "expirationDate": "270831",
        "id": "a8e5285e-384b-456e-84ec-4cf6664776f6",
        "maskPan": "***************0031",
        "signNeeded": true,
        "slipNumber": "000016",
        "terminalId": "S0040045",
        "transactionId": "S0040045",
        "transactionResult": "approved",
        "type": "purchase"
    },
    "reply": "transaction",
    "status": "ok"
}

cancel transaction example json:
16.09.2022 14:53::29.436
{
    "acquiringData": {
        "AID": null,
        "APN": null,
        "IIN": null,
        "RRN": null,
        "TSI": null,
        "TVR": null,
        "acquirerAgentName": "2can",
        "acquirerBankName": "ВТБ",
        "amount": 0,
        "approvalCode": null,
        "cardholder": null,
        "cashlessType": 2,
        "date": "2022-09-16T14:53:24.000+03:00",
        "errorCode": null,
        "errorMessage": null,
        "expirationDate": null,
        "id": "e52cde93-9a7a-45b5-959d-716c4b40caf4",
        "maskPan": null,
        "signNeeded": false,
        "slipNumber": null,
        "terminalId": "S0040045",
        "transactionId": "S0040045",
        "transactionResult": "declined",
        "type": "purchase"
    },
    "reply": "transaction",
    "status": "cancelled"
}



{
    "test": [
{
    "message": "keepalive"
},
{
    "message": "keepalive"
}
]
}